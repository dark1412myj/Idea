#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>
#include<algorithm>
#include<queue>
using namespace std;
class CSV_Reader
{
    char sep;
    ifstream fin;
    vector<string> split(string& s)
    {
        stringstream is(s);
        vector<string> V;
        string tmp;
		while(is)
		{
			if(is.peek()=='\"')
			{
				is.get();
				getline(is,tmp,'\"');
				is.get();
			}else
			{
				getline(is,tmp,sep);
			}
			if(tmp.size()&&
					(tmp[tmp.size()-1]=='\r'||tmp[tmp.size()-1]=='\n'))
				tmp.erase(tmp.end()-1,tmp.end());
            V.push_back(tmp);
		}
        return V;
    }
    vector<string> split(ifstream& fin)
    {
        vector<string> V;
        string s;
        getline(fin,s);
		if(s.size())
        	return split(s);
		return V;
    }
    string combine(vector<string> V,char sep=',')
    {
        string s;
        for(int i=0;i<V.size();++i)
        {
			s+="\"";
            s+=V[i];
			s+="\"";
            if(i<V.size()-1)
                s+=sep;
        }
        return s;
    }
public:
    vector<vector<string> > data;
    vector<string> title;
    CSV_Reader(string filename,char sep=',',bool has_title=true):sep(sep)
    {
        fin.open(filename);
        title = split(fin);
    }
    int operator [] (string name)
    {
        for(int i=0;i<title.size();++i)
        {
            if(name == title[i])
                return i;

        }
        throw "Not line";
        return -1;
    }
    void load()
    {
        while(fin)
		{
			auto x = split(fin);
			if(x.size())
				data.push_back(x);
		}
    }
    bool save(string pathname,char sep=0)
    {
        if(sep==0)
            sep=',';
        ofstream fou(pathname,ios::binary|ios::out);
        fou<<combine(title,sep)<<endl;
        for(int i=0;i<data.size();++i)
        {
            fou<<combine(data[i],sep)<<endl;
        }
        return true;
    }

};

struct cmp
{
    int item_id;
    int time_id;
    cmp(int item_id,int time_id):item_id(item_id),time_id(time_id) {}
    bool operator ()(const vector<string>& a,const vector<string>& b)const
    {
        if(a[item_id]!=b[item_id])
            return a[item_id]<b[item_id];
        return a[time_id]<b[time_id];
    }
};

int main()
{
    //CSV_Reader csv("myadd.csv");
    CSV_Reader csv("csv_test.csv");
    csv.load();
    ///csv[ "xxxx" ] 返回xxx那列的索引，如果不存在这样的列抛出异常
    for(int i=0;i<csv.title.size();++i)
    {
        cout<<csv.title[i]<<endl;
        for(int j=0;j<csv.data.size();++j)
            cout<<csv.data[j][ csv[ csv.title[i] ] ]<<endl;
    }
    return 0;
}
