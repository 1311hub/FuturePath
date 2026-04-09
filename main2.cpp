class Matching
{
    bool ismatch = false;
    public:
    void match_company(company *c,User &u)
    {
        if(u.sgpa<c->mincgpa)
        {
            return;
        }
        cout<<"--------------------"<<u.name<<", your cgpa is eligible for "<<c->companyname<<"----------------------"<<endl<<endl<<endl;
        for(int i = 0; i < 10; i++)
        {
            if(u.skills[i]>c->skills[i])
            {
                cout<<c->skillNames[i]<<" matches the norms of "<<c->companyname<<endl<<endl;
            }
        }
}
};
