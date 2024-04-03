#ifndef DATABASESS
#define DATABASESS

template<class T>
class Database{
	public:
		Database();
		void run();
	private:
		fstream database;
		ofstream opening;
		char fName[20];
		ostream& print(ostream&);
		void add(T&);
		bool find(const T&);
		void modify(const T&);
		friend ostream& operator<<(ostream& out, Database& db){
			return db.print(out);
		}
};
// Include template definitions here:
#include "database.cpp"
#endif
