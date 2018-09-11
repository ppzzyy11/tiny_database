#include<iostream>
#include<fstream>
#include<vector>
#include<unordered_map>

using namespace std;
bool output_newline=0;

ifstream fin;
ofstream fout;

vector<string> dates;//store the whole use strings
vector<bool> del;//whether the dates is deleted or not

unordered_map<string,vector<int>> rec;//attributes indexes

void Intersection(vector<int>& nums1,vector<int>& nums2)//nums1 num2 are sorted
{
    vector<int> res;
    int i=0;
    int j=0;
    while(i<nums1.size()&&j<nums2.size())
    {
        if(nums1[i]==nums2[j])
        {
            res.push_back(nums1[i]);
            i++;
            j++;
        }else if(nums1[i]>nums2[j])
        {
            j++;
        }else if(nums1[i]<nums2[j])
        {
            i++;
        }
    }
    nums1=res;
}

void Segmentation(const string& str,vector<string>& seg)
{
    int i=0;
    while(str[i]!='{')
    {
        i++;
    }
    i++;
    while(i<str.size())
    {
        int j=i;
        while(str[j]!=','&&str[j]!='}')
        {
            j++;
        }
        seg.push_back(str.substr(i,j-i));//
        i=j+1;
    }
}

void SemanticAnalysis(const string& str)
{
    if(str.substr(0,3)=="add")//add
    {
        dates.push_back(str.substr(4));
        del.push_back(0);
        vector<string> seg;
        Segmentation(str,seg);
        for(auto s:seg)
        {
            rec[s].push_back(dates.size()-1);
        }
    }else if(str.substr(0,3)=="del")//del
    {
        vector<string> seg;
        Segmentation(str,seg);
        vector<int> idxex;
        for(auto s:seg)
        {
            if(idxex.size()==0)
            {
                idxex=rec[s];
            }else
            {
                Intersection(idxex,rec[s]);
            }
        }
        for(auto i:idxex)
        {
            del[i]=1;
        }
    }else if(str.substr(0,3)=="get")//output
    {
        vector<string> seg;
        Segmentation(str,seg);

        vector<int> idxex;
        for(auto s:seg)
        {
            if(idxex.size()==0)
            {
                idxex=rec[s];
            }else
            {
                Intersection(idxex,rec[s]);
            }
        }

        bool output=0;
        for(int i=0;i<idxex.size();i++)
        {
            if(del[idxex[i]]==0)
            {
                fout<<dates[idxex[i]]<<'\n';
                output=1;
            }
        }
        if(output==1)
        {
            output_newline=1;
            fout<<'\n';
        }else
        {
            if(output_newline==1)
            {
                fout<<'\n';
            }
            output_newline=0;
        }
    }
}

int main(int argc,char** argv)
{
    if(argc<3) {return 1;}//too few arguments

    string in;
    string out;
    for(int i=6;argv[1][i]!='\0';i++)
    {
        in.push_back(argv[1][i]);
    }
    //cout<<"in:\t"<<in<<endl;
    for(int i=7;argv[2][i]!='\0';i++)
    {
        out.push_back(argv[2][i]);
    }
    //cout<<"out:\t"<<out<<endl;

    fin.open(in.c_str(),ios::in);
    if(!fin.is_open()) {cerr<<"can't open "<<in<<endl;return 1;}
    fout.open(out.c_str(),ios::out);
    if(!fout.is_open()) {cerr<<"can't open "<<out<<endl;return 1;}

    string str;
    while(getline(fin,str))
    {
        //cout<<str<<endl;
        SemanticAnalysis(str);
    }

    fin.close();
    fout.close();
    return 0;
}
