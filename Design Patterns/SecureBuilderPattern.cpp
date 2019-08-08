#include <iostream>
#include <string>
#include <list>

enum trust { COMPLETE, LITTLE, BOGUS };

using namespace std;

class Action
{
public:
	string action;
	void setAction(const string &aaction)
	{
		action = aaction;
	}
};

class Source {
public:
	string source;
	void setSource(const string &asource)
	{
		source = asource;
	}
};

class Feilds {
public:
	list<string> fields;
	void setFeild(list<string> & afields)
	{
		fields = afields;
	}
};

class Constraints
{
public:
	list<string> constraints;
	void setConstraints(list<string> &aconstraints)
	{
		constraints = aconstraints;
	}
};

class Query
{
public:
	Action action;
	Source source;
	Feilds fields;
	Constraints constraints;
	list<string>::iterator it;
	Query() {};

	string getQuerry() {
		string query = source.source + " " + action.action + " ";
		for (it = fields.fields.begin(); it != fields.fields.end(); it++)
			query = query + *it;
		query = query + " ";
		for (it = constraints.constraints.begin(); it != constraints.constraints.end(); ++it)
			query = query + *it;
		return query;
	} // getQuery

	void emptyQuery()
	{
		source.source = "empty";
		action.action = "";
		fields.fields.clear();
		constraints.constraints.clear();
	} //emptyQuery
};

class TrustLevel
{
public:
	trust level;
};

class Subject
{
private:
	int ipAddr;
	TrustLevel trustLevel;
public:
	Subject(int newIpAddr, trust atrust)
	{
		ipAddr = newIpAddr;
		trustLevel.level = atrust;
	}

	TrustLevel getTrustLevel()
	{
		return trustLevel;
	}

	~Subject()
	{
		this->ipAddr = 0;
		this->trustLevel.level = BOGUS;
	}

	TrustLevel getTrustLevel() const { return trustLevel; }

	int getIpAddr() const { return ipAddr; }
};

class QueryBuilder {
public:
	virtual void addField(const string &f) {}
	virtual void addConstraint(const string &c) {}
	virtual void setSourceEmployee() {}
	virtual void setSourceCustomer() {}
	virtual void setActionView() {}
	virtual void setActionModify() {}
	virtual Query getQuery() = 0;
};

class CompleteTrustQueryBuilder : public QueryBuilder
{
private:
	string action;
	string source;
	list<string> fields;
	list<string> constraints;
	Query query;
public:
	CompleteTrustQueryBuilder() {
		source = "";
		action = "";
	}
	void addFeild(const string &f)
	{
		if ((f == "ID") || (f == "ADDRESS") || (f == "FIRST_NAME") || (f == "LAST_NAME") || (f == "BIRTH_DATE"))
		{
			fields.push_back(f);
		}
		else cout << "Feild" + f + "is unknown.";
	}
	void addContraint(const string &c)
	{
		constraints.push_back(c);
	}
	void setSourceEmployee()
	{
		source = "Employee";
	}
	void setSourceCustomer()
	{
		source = "customer";
	}
	void setActionView()
	{
		action = "view";
	}
	void setActionModify()
	{
		action = "modify";
	}

	Query getQuery() {
		if ((action == "") || (source == "") || (fields.size() == 0))
		{
			cout << "\nCannot create query. Information is missing.\n";
			query.emptyQuery();
		}
		else
		{
			// create and return query.

			query.source.setSource(source);
			query.action.setAction(action);
			query.fields.setFeild(fields);
			query.constraints.setConstraints(constraints);
		}
		return query;
	}
};

class LittleTrustQueryBuilder : public QueryBuilder
{
private:
	string action;
	string source;
	list<string> fields;
	list<string> constraints;
	Query query;
public:
	LittleTrustQueryBuilder()
	{
		source = "";
		action = "";
	}
	void addFiled(const string &f)
	{
		if ((f == "FIRST_NAME") || (f == "LAST_NAME") || (f == "BIRTH_DATE"))
		{
			fields.push_back(f);
		}
		else if((f == "ID") || (f == "ADDRESS")) // The user cannot access the given field
		{
			cout << "\nThe user cannot access the " + f + " field.\n";
		}
		else // The field provided is not known.
		{
			cout << "Field " + f + " is unknown.";
		}
	}

	void addConstraint(const string &f)
	{
		constraints.push_back(f);
	}

	void setSourceEmployee()
	{
		source = "employee";
	}

	void setSourceCustomer()
	{
		cout << "\nThe user canot access the customer data source.\n";
	}

	void setActionView()
	{
		action = "view";
	}

	void setActionModify()
	{
		cout << "\nThe user cannot modify records.\n";
	}

	Query getQuery()
	{
		if ((action == "") || (source == "") || (fields.size() == 0))
		{
			cout << "\nCannot create query. Information is missing.\n";
			query.emptyQuery();
		}
		else
		{
			query.source.setSource(source);
			query.action.setAction(action);
			query.fields.setFeild(fields);
			query.constraints.setConstraints(constraints);
		}
		return query;
	}

};

class BannedTrustQueryBuilder : public QueryBuilder
{
private:
	Query query;
public:
	Query getQuery()
	{
		cout << "A banned user cannot access the data";
		query.emptyQuery();
		return query;
	} //getQuery
}; // BannedTrustQueryBuilder

class QueryDirector
{
private:
	QueryBuilder *builder;
public:
	QueryDirector(QueryBuilder *newBuilder) { builder = newBuilder; };
	// Query building methods.

	Query makeQueryGeneral()
	{
		// Build the query.

		builder->setSourceEmployee();
		builder->setActionView();
		builder->addField("LAST_NAME");
		builder->addConstraint("UNIQUE");
		Query query = builder->getQuery();
		return query;
	} //makeQuery

	Query makeQueryProtected()
	{
		// Build the query.
		builder->setSourceCustomer();
		builder->setActionModify();
		builder->addField("ID");
		builder->addConstraint("UNIQUE");
		Query query = builder->getQuery();
		return query;
	} //make Query
}; //QueryDirector

void main()
{
	Subject *currSubject = new Subject(12, LITTLE); // COMPLETE LITTLE BOGUS
	QueryBuilder *builder;

	TrustLevel trust = currSubject->getTrustLevel();

	if (trust.level == COMPLETE)
	{
		builder = new CompleteTrustQueryBuilder();
	}
	else if (trust.level == LITTLE)
	{
		builder = new LittleTrustQueryBuilder();
	}
	else
	{
		builder = new BannedTrustQueryBuilder();
	}

	QueryDirector direct(builder);
	Query query = direct.makeQueryProtected();
	//Query query = direct.makeQueryGeneral();
	cout << "\nquery =" << query.getQuerry() << endl;
	system("pause");
}
