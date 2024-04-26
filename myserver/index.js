const express  = require('express');
const cookieParser = require('cookie-parser');
const app = express();
const host = "localhost"
const port = 8080;

app.use(express.urlencoded({extended: true}));
app.use(cookieParser())
app.get('/', (req,res) => {
	res.type('text/plain');
	if (req.cookies.naolc === undefined) {
		res.cookie('naolc', '1')
		res.send('Reques first time \n')
	}
	else
		res.send('Welcome back, naol\n');
	})
app.post('/',(req, res) => {
	res.send(`${req.body.message} \n`)
})
app.post('/echo',(req, res)=> {
	res.send(`${req.body.message}\n`)
})
app.get('/echo/:message', (req, res) => {
	res.send(`${req.params.message}\n`)
})
app.get('/ip', (req, res) => {
	res.type('text/plain');
	res.send(`${req.ip} \n `);
})
/*
app.get('/?message', (req, res) => {
	res.send(req.query.message)
})
*/
app.listen(port, host, ()=>{
	console.log(`Server ready at http://${host}:${port}`)
})
