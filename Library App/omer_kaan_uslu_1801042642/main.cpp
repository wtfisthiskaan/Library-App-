#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

/*------------------------CATALOG CLASS---------------------*/

class catalog{

public:
	/*---------------GETTERS AND SETTERS--------------------*/
	string getTitle();
	string getYear();
	string getGenre();
	void setTitle(string str);
	void setYear(string str);
	void setGenre(string str);
private:
	/*------------------COMMON VARIABLES--------------------*/
	string title;
	string year;
	string genre;
};
				/*Catalog Class Member Functions*/

/*-------------GETTERS AND SETTERS DEFINING-----------------*/

string catalog::getTitle(){
	return title;
}
string catalog::getYear(){
	return year;
}
string catalog::getGenre(){
	return genre;
}

void catalog::setTitle(string str){
	title=str;
}
void catalog::setYear(string str){
	year=str;
}
void catalog::setGenre(string str){
	genre=str;
}

/*------------------------BOOK CLASS------------------------*/

class book: public catalog{
public:
	/*---------------GETTERS AND SETTERS--------------------*/
	string getAuthors(){
		return authors;
	}
	string getTags(){
		return tags;
	}
	void setAuthors(string str){
		authors=str;
	}
	void setTags(string str){
		tags=str;
	}

	string printed_line(){//<title> <authors> <year> <tags>
		/* this func returns string which is ready to print.*/
		/*-------------adding quotes with + operator--------*/
		string str="\"";
		str+=getTitle();
		str+="\" ";
		str+="\"";
		str+=getAuthors();
		str+="\" ";
		str+="\"";
		str+=getYear();
		str+="\" ";
		str+="\"";
		str+=getTags();
		str+="\" ";

		return str;
	}

private:
	/*-------------------UNIQUE MEMBER FUNCTIONS------------*/
	string authors;
	string tags;
};

/*------------------------MUSIC CLASS-----------------------*/

class music: public catalog{
public:
	/*---------------GETTERS AND SETTERS--------------------*/
	string getArtists(){
		return artists;
	}
	void setArtists(string str){
		artists=str;
	}
	string printed_line(){//<title> <artists> <year> <genre>
		/* this func returns string which is ready to print.*/
		/*-------------adding quotes with + operator--------*/
		string str="\"";
		str+=getTitle();
		str+="\" ";
		str+="\"";
		str+=getArtists();
		str+="\" ";
		str+="\"";
		str+=getYear();
		str+="\" ";
		str+="\"";
		str+=getGenre();
		str+="\" ";
		return str;
	}

private:
	/*-------------------UNIQUE MEMBER FUNCTIONS------------*/
	string artists;
};

/*------------------------MOVIE CLASS-----------------------*/

class movie: public catalog{
public:
	/*---------------GETTERS AND SETTERS--------------------*/
	string getDirector(){
		return director;
	}
	string getStarring(){
		return starring;
	}
	void setDirector(string str){
		director=str;
	}
	void setStarring(string str){
		starring=str;
	}

	string printed_line(){//<title> <director> <year> <genre> <starring>
		/* this func returns string which is ready to print.*/
		/*-------------adding quotes with + operator--------*/
		string str="\"";
		str+=getTitle();
		str+="\" ";
		str+="\"";
		str+=getDirector();
		str+="\" ";
		str+="\"";
		str+=getYear();
		str+="\" ";
		str+="\"";
		str+=getGenre();
		str+="\" ";
		str+="\"";
		str+=getStarring();
		str+="\" ";
		return str;
	}
private:
	/*-------------------UNIQUE MEMBER FUNCTIONS------------*/
	string director;
	string starring;
};

/*-------------------STANDALONE FUNCTIONS-------------------*/

void parse_strings(vector<string> &datas,string str){//this func prepares and parses string to write into related object.
	int places[2];
	int flag=0;
	int i;
	string str2;
	for(i=0;i<str.length();i++){
		if(str[i]=='"'){//first " is found,second is going to be searched
			places[flag]=i;
			flag++;
			if(flag==2){//second found.
				flag=0;
				if(places[1]-1==places[0])
					str2="";
				else
					str2=str.substr(places[0]+1,places[1]-1-places[0]);
				datas.push_back(str2);
			}
		}
	}
}


int main() {
	/*------------Defining variables which will be used-----*/
	ifstream inData;
	inData.open("data.txt");
	string temp;
	int i,j;
	inData>>temp;//take first word
	ofstream outData;
	outData.open("output.txt");
	if(temp=="book"){//if it is book catalog
		/*------------------------CATALOG READ PART---------*/
		outData<<"Catalog Read: "<<temp<<endl;
		int count=0;
		vector<book> v;
    	getline(inData,temp);//after reading first word with >> operator, getline reads '\n' for first line. this line blocks it before while loop
		while(getline(inData,temp)){//while loop to get lines and write those in object.
			vector<string> datas;
	  		parse_strings(datas,temp);//parse and write those into string vector
	   		try {
			    for(i=0;i<v.size();i++){
			    	if(v[i].getTitle()==datas[0]){//check duplicate entries
			    		throw 0;
			    	}
			    }
			    if(datas.size()!=4){//there is missing fields or more fields than expected
			    	throw 1;
			    }
			    else{//check is done. line is ready to be objectified.
			    	book temporary;
			    	count++;
			    	temporary.setTitle(datas[0]);
			    	temporary.setAuthors(datas[1]);
			    	temporary.setYear(datas[2]);
			    	temporary.setTags(datas[3]);
			    	v.push_back(temporary);
			  		}
			  	}
			 catch (int num) {
			 	if(num==0)//if num is 0 it is dup entry
			 		outData<<"Exception: duplicate entry"<<endl;
			 	else//if 1, it is missing field
			 		outData<<"Exception: missing field"<<endl;
			    outData<<temp<<endl;
			  }
			  

		}
		outData<<count<<" unique entries"<<endl;

		/*-----------------COMMANDS READ PART---------------*/
  		ifstream inCommand;
  		inCommand.open("commands.txt");
  		while(getline(inCommand,temp)){//get commands
  			try{
	  			vector<string> datas;
	  			parse_strings(datas,temp);
	  			if(temp.find("search")==0){//<title> <authors> <year> <tags>
	  				if(datas.size()!=2)
	  					throw temp;

	  				if(datas[1]=="title"){
	  					outData<<temp<<endl;
	  					for(i=0;i<v.size();i++){
	  						if(v[i].getTitle().find(datas[0]) != std::string::npos){//check if realated string contains argument of command
	  							
	  							outData<<v[i].printed_line()<<endl;
	  						}
	  					}
	  				}

	  				else if(datas[1]=="authors"){
	  					for(i=0;i<v.size();i++){
	  						if(v[i].getAuthors().find(datas[0]) != std::string::npos){
	  							outData<<temp<<endl;
	  							outData<<v[i].printed_line()<<endl;
	  						}
	  					}
	  				}

	  				else if(datas[1]=="year"){
	  					outData<<temp<<endl;
	  					for(i=0;i<v.size();i++){
	  						if(v[i].getYear().find(datas[0]) != std::string::npos){
	  							
	  							outData<<v[i].printed_line()<<endl;
	  						}
	  					}
	  				}

	  				else if(datas[1]=="tags"){
	  					outData<<temp<<endl;
	  					for(i=0;i<v.size();i++){
	  						if(v[i].getTags().find(datas[0]) != std::string::npos){
	  							outData<<v[i].printed_line()<<endl;
	  						}
	  					}
	  				}
	  				else
	  					throw temp;
	  			}
	  			else if(temp.find("sort")==0){//<title> <authors> <year> <tags>
	  				if(datas.size()!=1)
	  					throw temp;

	  				if(datas[0]=="title"){
	  					outData<<temp<<endl;
	  					vector<string> sorting;
	  					for(i=0;i<v.size();i++){
	  						sorting.push_back(v[i].getTitle());
	  					}
	  					sort(sorting.begin(), sorting.end());
	  					for(i=0;i<sorting.size();i++){
	  						for(j=0;j<v.size();j++)
	  							if(v[j].getTitle()==sorting[i])
	  								outData<<v[j].printed_line()<<endl;
	  							
	  					}
	  				}

	  				else if(datas[0]=="authors"){
	  					outData<<temp<<endl;
	  					vector<string> sorting;
	  					for(i=0;i<v.size();i++){
	  						sorting.push_back(v[i].getAuthors());
	  					}
	  					sort(sorting.begin(), sorting.end());
	  					for(i=0;i<sorting.size();i++){
	  						for(j=0;j<v.size();j++)
	  							if(v[j].getAuthors()==sorting[i])
	  								outData<<v[j].printed_line()<<endl;
	  							
	  					}
	  					
	  				}

	  				else if(datas[0]=="year"){
	  					outData<<temp<<endl;
	  					vector<string> sorting;
	  					for(i=0;i<v.size();i++){
	  						sorting.push_back(v[i].getYear());
	  					}
	  					sort(sorting.begin(), sorting.end());
	  					for(i=0;i<sorting.size();i++){
	  						for(j=0;j<v.size();j++)
	  							if(v[j].getYear()==sorting[i])
	  								outData<<v[j].printed_line()<<endl;
	  							
	  					}
	  				}

	  				else if(datas[0]=="tags"){
	  					outData<<temp<<endl;
	  					vector<string> sorting;
	  					for(i=0;i<v.size();i++){
	  						sorting.push_back(v[i].getTags());
	  					}
	  					sort(sorting.begin(), sorting.end());
	  					for(i=0;i<sorting.size();i++){
	  						for(j=0;j<v.size();j++)
	  							if(v[j].getTags()==sorting[i])
	  								outData<<v[j].printed_line()<<endl;
	  							
	  					}
	  				}
	  				else
	  					throw temp;

	  			}
	  			else
	  				throw temp;
	  			}
	  			catch(string str){//str is current command line
	  				outData<<"Exception: command is wrong"<<endl;
	  				outData<<str<<endl;
	  			}
	  			
  		}

	}
	/*---------the rest is the same algorithm.--------------*/
	/*------------there won't be comment below--------------*/
	else if(temp=="music"){
		/*------------------------CATALOG READ PART---------*/
		outData<<"Catalog Read: "<<temp<<endl;
		int count=0;
		vector<music> v;
    getline(inData,temp);
		while(getline(inData,temp)){
			vector<string> datas;
	  		parse_strings(datas,temp);
	   		try {
			    for(i=0;i<v.size();i++){
			    	if(v[i].getTitle()==datas[0]){
			    		throw 0;
			    	}
			    }
			    if(datas.size()!=4){
			    	throw 1;
			    }
			    else{
			    	music temporary;
			    	count++;
			    	temporary.setTitle(datas[0]);
			    	temporary.setArtists(datas[1]);
			    	temporary.setYear(datas[2]);
			    	temporary.setGenre(datas[3]);
			    	v.push_back(temporary);
			  		}
			  	}
			 catch (int num) {
			 	if(num==0)
			 		outData<<"Exception: duplicate entry"<<endl;
			 	else
			 		outData<<"Exception: missing field"<<endl;
			    outData<<temp<<endl;
			  }
			  

		}
		outData<<count<<" unique entries"<<endl;

		/*-----------------COMMANDS READ PART---------------*/
  		ifstream inCommand;
  		inCommand.open("commands.txt");
  		while(getline(inCommand,temp)){
  			try{
	  			//outData<<temp<<endl;
	  			vector<string> datas;
	  			parse_strings(datas,temp);
	  			if(temp.find("search")==0){//<title> <artists> <year> <genre>
	  				if(datas.size()!=2)
	  					throw temp;

	  				if(datas[1]=="title"){
	  					outData<<temp<<endl;
	  					for(i=0;i<v.size();i++){
	  						if(v[i].getTitle().find(datas[0]) != std::string::npos){
	  							
	  							outData<<v[i].printed_line()<<endl;
	  						}
	  					}
	  				}

	  				else if(datas[1]=="artists"){
	  					for(i=0;i<v.size();i++){
	  						if(v[i].getArtists().find(datas[0]) != std::string::npos){
	  							outData<<temp<<endl;
	  							outData<<v[i].printed_line()<<endl;
	  						}
	  					}
	  				}

	  				else if(datas[1]=="year"){
	  					outData<<temp<<endl;
	  					for(i=0;i<v.size();i++){
	  						if(v[i].getYear().find(datas[0]) != std::string::npos){
	  							
	  							outData<<v[i].printed_line()<<endl;
	  						}
	  					}
	  				}

	  				else if(datas[1]=="genre"){
	  					outData<<temp<<endl;
	  					for(i=0;i<v.size();i++){
	  						if(v[i].getGenre().find(datas[0]) != std::string::npos){
	  							
	  							outData<<v[i].printed_line()<<endl;
	  						}
	  					}
	  				}
	  				else
	  					throw temp;


	  			}
	  			else if(temp.find("sort")==0){//<title> <artists> <year> <genre>
	  				if(datas.size()!=1)
	  					throw temp;

	  				if(datas[0]=="title"){
	  					outData<<temp<<endl;
	  					vector<string> sorting;
	  					for(i=0;i<v.size();i++){
	  						sorting.push_back(v[i].getTitle());
	  					}
	  					sort(sorting.begin(), sorting.end());
	  					for(i=0;i<sorting.size();i++){
	  						for(j=0;j<v.size();j++)
	  							if(v[j].getTitle()==sorting[i])
	  								outData<<v[j].printed_line()<<endl;
	  							
	  					}
	  				}

	  				else if(datas[0]=="artists"){
	  					outData<<temp<<endl;
	  					vector<string> sorting;
	  					for(i=0;i<v.size();i++){
	  						sorting.push_back(v[i].getArtists());
	  					}
	  					sort(sorting.begin(), sorting.end());
	  					for(i=0;i<sorting.size();i++){
	  						for(j=0;j<v.size();j++)
	  							if(v[j].getArtists()==sorting[i])
	  								outData<<v[j].printed_line()<<endl;
	  							
	  					}
	  					
	  				}

	  				else if(datas[0]=="year"){
	  					outData<<temp<<endl;
	  					vector<string> sorting;
	  					for(i=0;i<v.size();i++){
	  						sorting.push_back(v[i].getYear());
	  					}
	  					sort(sorting.begin(), sorting.end());
	  					for(i=0;i<sorting.size();i++){
	  						for(j=0;j<v.size();j++)
	  							if(v[j].getYear()==sorting[i])
	  								outData<<v[j].printed_line()<<endl;
	  							
	  					}
	  				}

	  				else if(datas[0]=="genre"){
	  					outData<<temp<<endl;
	  					vector<string> sorting;
	  					for(i=0;i<v.size();i++){
	  						sorting.push_back(v[i].getGenre());
	  					}
	  					sort(sorting.begin(), sorting.end());
	  					for(i=0;i<sorting.size();i++){
	  						for(j=0;j<v.size();j++)
	  							if(v[j].getGenre()==sorting[i])
	  								outData<<v[j].printed_line()<<endl;
	  							
	  					}
	  				}
	  				else
	  					throw temp;

	  			}
	  			else
	  				throw temp;
	  			}
	  			catch(string str){
	  				outData<<"Exception: command is wrong"<<endl;
	  				outData<<str<<endl;
	  			}
	  			
  		}




	}
	else if(temp=="movie"){
		/*------------------------CATALOG READ PART---------*/
		outData<<"Catalog Read: "<<temp<<endl;
		int count=0;
		vector<movie> v;
    getline(inData,temp);
		while(getline(inData,temp)){
			vector<string> datas;
	  		parse_strings(datas,temp);
	   		try {
			    for(i=0;i<v.size();i++){
			    	if(v[i].getTitle()==datas[0]){
			    		throw 0;
			    	}
			    }
			    if(datas.size()!=5){
			    	throw 1;
			    }
			    else{
			    	movie temporary;
			    	count++;
			    	temporary.setTitle(datas[0]);
			    	temporary.setDirector(datas[1]);
			    	temporary.setYear(datas[2]);
			    	temporary.setGenre(datas[3]);
			    	temporary.setStarring(datas[4]);
			    	v.push_back(temporary);
			  		}
			  	}
			 catch (int num) {
			 	if(num==0)
			 		outData<<"Exception: duplicate entry"<<endl;
			 	else
			 		outData<<"Exception: missing field"<<endl;
			    outData<<temp<<endl;
			  }
		}
		outData<<count<<" unique entries"<<endl;

		
  		/*-----------------COMMANDS READ PART---------------*/
  		ifstream inCommand;
  		inCommand.open("commands.txt");
  		while(getline(inCommand,temp)){
  			try{
	  			//outData<<temp<<endl;
	  			vector<string> datas;
	  			parse_strings(datas,temp);
	  			if(temp.find("search")==0){//<title> <director> <year> <genre> <starring>
	  				if(datas.size()!=2)
	  					throw temp;

	  				if(datas[1]=="title"){
	  					outData<<temp<<endl;
	  					for(i=0;i<v.size();i++){
	  						if(v[i].getTitle().find(datas[0]) != std::string::npos){
	  							
	  							outData<<v[i].printed_line()<<endl;
	  						}
	  					}
	  				}

	  				else if(datas[1]=="director"){
	  					for(i=0;i<v.size();i++){
	  						if(v[i].getDirector().find(datas[0]) != std::string::npos){
	  							outData<<temp<<endl;
	  							outData<<v[i].printed_line()<<endl;
	  						}
	  					}
	  				}

	  				else if(datas[1]=="year"){
	  					outData<<temp<<endl;
	  					for(i=0;i<v.size();i++){
	  						if(v[i].getYear().find(datas[0]) != std::string::npos){
	  							
	  							outData<<v[i].printed_line()<<endl;
	  						}
	  					}
	  				}

	  				else if(datas[1]=="genre"){
	  					outData<<temp<<endl;
	  					for(i=0;i<v.size();i++){
	  						if(v[i].getGenre().find(datas[0]) != std::string::npos){
	  							
	  							outData<<v[i].printed_line()<<endl;
	  						}
	  					}
	  				}

	  				else if(datas[1]=="starring"){
	  					outData<<temp<<endl;
	  					for(i=0;i<v.size();i++){
	  						if(v[i].getStarring().find(datas[0]) != std::string::npos){

	  							outData<<v[i].printed_line()<<endl;
	  						}
	  					}
	  				}
	  				else
	  					throw temp;


	  			}
	  			else if(temp.find("sort")==0){
	  				if(datas.size()!=1)
	  					throw temp;

	  				if(datas[0]=="title"){
	  					outData<<temp<<endl;
	  					vector<string> sorting;
	  					for(i=0;i<v.size();i++){
	  						sorting.push_back(v[i].getTitle());
	  					}
	  					sort(sorting.begin(), sorting.end());
	  					for(i=0;i<sorting.size();i++){
	  						for(j=0;j<v.size();j++)
	  							if(v[j].getTitle()==sorting[i])
	  								outData<<v[j].printed_line()<<endl;
	  							
	  					}
	  				}

	  				else if(datas[0]=="director"){
	  					outData<<temp<<endl;
	  					vector<string> sorting;
	  					for(i=0;i<v.size();i++){
	  						sorting.push_back(v[i].getDirector());
	  					}
	  					sort(sorting.begin(), sorting.end());
	  					for(i=0;i<sorting.size();i++){
	  						for(j=0;j<v.size();j++)
	  							if(v[j].getDirector()==sorting[i])
	  								outData<<v[j].printed_line()<<endl;
	  							
	  					}
	  					
	  				}

	  				else if(datas[0]=="year"){
	  					outData<<temp<<endl;
	  					vector<string> sorting;
	  					for(i=0;i<v.size();i++){
	  						sorting.push_back(v[i].getYear());
	  					}
	  					sort(sorting.begin(), sorting.end());
	  					for(i=0;i<sorting.size();i++){
	  						for(j=0;j<v.size();j++)
	  							if(v[j].getYear()==sorting[i])
	  								outData<<v[j].printed_line()<<endl;
	  							
	  					}
	  				}

	  				else if(datas[0]=="genre"){
	  					outData<<temp<<endl;
	  					vector<string> sorting;
	  					for(i=0;i<v.size();i++){
	  						sorting.push_back(v[i].getGenre());
	  					}
	  					sort(sorting.begin(), sorting.end());
	  					for(i=0;i<sorting.size();i++){
	  						for(j=0;j<v.size();j++)
	  							if(v[j].getGenre()==sorting[i])
	  								outData<<v[j].printed_line()<<endl;
	  							
	  					}
	  				}

	  				else if(datas[0]=="starring"){
	  					outData<<temp<<endl;
	  					vector<string> sorting;
	  					for(i=0;i<v.size();i++){
	  						sorting.push_back(v[i].getStarring());
	  					}
	  					sort(sorting.begin(), sorting.end());
	  					for(i=0;i<sorting.size();i++){
	  						for(j=0;j<v.size();j++)
	  							if(v[j].getStarring()==sorting[i])
	  								outData<<v[j].printed_line()<<endl;
	  							
	  					}
	  				}
	  				else
	  					throw temp;

	  			}
	  			else
	  				throw temp;
	  			}
	  			catch(string str){
	  				outData<<"Exception: command is wrong"<<endl;
	  				outData<<str<<endl;
	  			}
	  			
  		}
  		inCommand.close();
    } 
    inData.close();
    outData.close();
}
