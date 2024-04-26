const express = require("express");
const app = express();
const host = "localhost";
const port = 8080;

app.set('view engine', 'ejs');
const sqlite3 = require('sqlite3');
const db = new sqlite3.Database('messages.sqlite3');

app.use(express.static("public"));

const cookieParser = require('cookie-parser');
app.use(cookieParser());

const { v4: uuidv4 } = require('uuid');

app.use(express.urlencoded({ extended: true}));

// Array to store messages
let messages = [];

app.post('/', (req,res) => {
	// Only JSON enabled requests
	if ( req.headers.accept != "application/json")
	{
		res.sendStatus(404);
		return;
	}

	// Locate cookies in the request
	let uuid = req.cookies.uuid;

	// If there is no uuid cookie, create a new one
	if ( uuid === undefined)
		uuid = uuidv4();
	// Add message first in the message array
	messages.unshift({ uuid: uuid, message: req.body.message});

	// Collect all previous messages for uuid
	let user_entries = [];
	messages.forEach( (entry) => {
		if ( entry.uuid == req.cookies.uuid )
			user_entries.push(entry.message)
	})

	// Update cookie expiration date
	let expires = new Date(Date.now());
	expires.setDate(expires.getDate() + 30);
	res.cookie('uuid', uuid, { expires: expires });

	// Send back JSON response
	res.json(user_entries)
});

app.post('/template', (req, res) => {
	let uuid = req.cookies.uuid
	if ( uuid === undefined )
		uuid = uuidv4()
	messages.unshift({uuid: uuid, message: req.body.message})

	let user_entries = []
	messages.forEach( (entry) => {
		if ( entry.uuid == req.cookies.uuid )
			user_entries.push(entry.message)
	})
	let expires = new Date(Date.now());
	expires.setDate(expires.getDate() + 30);
	res.cookie('uuid', uuid, { expires: expires })
	if ( req.headers.accept == "application/json" )
		res.json(user_entries)
	else
		res.render('index', {title: "My messages", messages: user_entries})
})

app.get('/template', (req, res) => {
	let uuid = req.cookies.uuid
	let user_entries = []
	if ( uuid === undefined ){
		uuid = uuidv4()
	}
	else {
		messages.forEach( (entry) => {
			if ( entry.uuid == req.cookies.uuid )
				user_entries.push(entry.message)
		})
	}
	let expires = new Date(Date.now());
	expires.setDate(expires.getDate() + 30);
	res.cookie('uuid', uuid, { expires: expires })
	if ( req.headers.accept == "application/json" )
		res.json(user_entries)
	else
		res.render('index', {title: "My messages", messages: user_entries})
})

app.get('/', (req, res) => {
	// Only JSON enabled requests
	if ( req.headers.accept != "application/json" )
	{
		res.sendStatus(404);
		return;
	}

	// Locate cookies in the request
	let uuid = req.cookies.uuid;

	// Client's own messages
	let user_entries = [];
	// If there is no uuid cookie, create a new one
	if ( uuid === undefined ){
		uuid = uuidv4();
	}
	else {
		// Collect messages for uuid
		messages.forEach( (entry) => {
			if ( entry.uuid == req.cookies.uuid )
				user_entries.push(entry.message)
		})
	}
	// Update cookie expiration date
	let expires = new Date(Date.now());
	expires.setDate(expires.getDate() + 30);
	res.cookie('uuid', uuid, { expires: expires });
	// Send back JSON response
	res.json(user_entries);
})

app.set('views','./templates');

db.run('CREATE TABLE IF NOT EXISTS messages (id INTEGER PRIMARY KEY AUTOINCREMENT, uuid CHAR(36), message TEXT)');

app.post('/fromdb',(req, res) => {
	let uuid = req.cookies.uuid;
	if (uuid === undefined)
		uuid = uuidv4();

	// Insert new message into the database
	db.run('INSERT INTO messages (uuid, message) VALUES (?,?)', uuid, req.body.message);

	// If an error  occurrs, err object contain the error message.
	db.all('SELECT id, message FROM messages WHERE uuid = ?',uuid, (err, rows) => {
		let expires = new Date(Date.now());
		expires.setDate(expires.getDate() +30);
		res.cookie('uuid',uuid, { expires: expires});

		if ( req.headers.accept == "application/json")
			res.json(rows);
		else
			res.render('index', {title: "My DB Message", rows: rows})
	});

	});

app.get('/fromdb',(req, res) => {
	let uuid = req.cookies.uuid;
	if (uuid === undefined)
		uuid = uuidv4();

	else
	{
	// If an error  occurrs, err object contain the error message.
	db.all('SELECT id, message FROM messages WHERE uuid = ?',uuid, (err, rows) => {
		let expires = new Date(Date.now());
		expires.setDate(expires.getDate() +30);
		res.cookie('uuid',uuid, { expires: expires});

		if ( req.headers.accept == "application/json")
			res.json(rows);
		else
			res.render('index', {title: "My DB Message", rows: rows})
	});
	}

	});


app.post('/fromdb:id', (req, res) => {
	let uuid = req.cookies.uuid;

	if ( uuid === undefined ) {
		uuid = uuidv4();

		// 401 Unauthorized
		res.sendStatus(401);
	}
	else {
		// Update the stored message
		// using named parameters
		let param = {
			$message: req.body.message,
			$id: req.params.id,
			$uuid: uuid
		}
		db.run('UPDATE messages SET message = $message WHERE id = $id AND uuid = $uuid', param, function(err){
			if (this.changes >0)
			{
				// A 204 (No Content) status code means the action has
				// been enacted and no further information is to be supplied.
				res.sendStatus(204);
			}
			else
				res.sendStatus(404);
		})
	}
});

app.delete('/delete/fromdb:id', (req, res) => {
	let uuid = req.cookies.uuid
	if ( uuid === undefined ){
		uuid = uuidv4()
		res.sendStatus(401)
	}
	else {
		// Named parameters
		let param = {
			$id: req.params.id,
			$uuid: uuid
		}
		db.run('DELETE FROM messages WHERE id = $id AND uuid = $uuid', param, function(err){
			if ( this.changes > 0 )
				res.sendStatus(204)
			else
				res.sendStatus(404)
		})
	}
})

const server = app.listen(port, host, () => {
	console.log(`Server ready at http://${host}:${port}`);
});

process.on('SIGINT', () => {
	db.close()
	server.close()
	console.log('\n HTTP server closed\n')
})


