#include <bits/stdc++.h>

#define exp first
#define coef second

using namespace std;

ifstream f("text.in");
ofstream g("text.out");
class Pereche;
class Polinom{

    list <pair<double, double>> L;

  public:
    friend class Pereche;
    friend ostream& operator<<(ostream& os, list<pair<double, double>>& p);
    friend istream& operator>>(istream& in, list<pair<double, double>>& p);
    Polinom operator+(Polinom&);
    Polinom operator-(Polinom&);
    Polinom operator*(Polinom&);
    void setElementPolinom(pair<double, double>);
    list< pair<double, double>>& getList();
    void sortList();
    double calcul(double);
};

class Pereche{

    pair<double, double> pereche;

  public:
    friend ostream& operator<<(ostream& os, pair<double, double>& p);
    friend istream& operator>>(istream& in, pair<double, double>& p);
    pair <double, double>& getPereche();
    void setPereche(pair<double, double>);
};

list<pair<double, double>>& Polinom::getList()
{
    return L;
}

bool cmp(const pair<double, double>& p1, const pair<double, double>& p2)
{
    return (p1.exp < p2.exp);
}

void Polinom::sortList()
{
    L.sort(cmp);
}

istream& operator>>(istream& in, Pereche& p)
{
    pair<double, double> pereche;
    f >> pereche.coef >> pereche.exp;
    p.setPereche(pereche);
}

void Polinom::setElementPolinom(pair<double, double> p)
{
    L.push_back(make_pair(p.exp, p.coef));
}

int n;

istream& operator>>(istream& in, Polinom& P)
{
    Pereche p;
    pair<double, double> auxPereche;
    f >> n;
    for(int i = 0; i < n; i++)
    {
        cin >> p;
        auxPereche = p.getPereche();
        P.setElementPolinom(auxPereche);
    }
    P.sortList();
}

ostream& operator<<(ostream& os, Polinom& p)
{
    int i = 0;
    list< pair<double, double>> L = p.getList();
    for(list<pair<double, double>>::iterator it=L.begin(); it != L.end(); i++, ++it)
    {
        if((*it).exp == 0) cout << (*it).coef << " + ";
        else if((*it).exp == 1)
             {
               if((*it).coef == 1) cout <<"X + ";
               else cout << (*it).coef <<"X + ";
             }
            else if(i == L.size() - 1)
                 {
                    if((*it).coef == 1) cout << "X^" << (*it).exp;
                    else cout << (*it).coef <<"X^" << (*it).exp;
                 }
                else if(i != L.size())
                     {
                        if((*it).coef == 1) cout << "X^" << (*it).exp << " + ";
                        else cout << (*it).coef << "X^" << (*it).exp << " + ";
                    }
    }
    cout << '\n';
}


pair<double, double>& Pereche::getPereche()
{
    return pereche;
}

void Pereche::setPereche(pair<double, double> p)
{
    pereche.exp = p.exp;
    pereche.coef = p.coef;
}

ostream& operator<<(ostream& os, Pereche& p)
{
    pair<double, double> pereche = p.getPereche();
    if(pereche.exp == 0) cout << pereche.coef;
    else if(pereche.exp == 1) cout << pereche.coef <<"X"<<' ';
    else cout << pereche.coef << "X^" << pereche.exp<<' ';
    return os;
}

Polinom Polinom::operator+(Polinom& aux)
{
    Polinom rez;
    list< pair<double, double>> L1 = (*this).getList();
    list< pair<double, double>> L2 = aux.getList();

    list<pair<double, double>>::iterator iterator;
    list<pair<double, double>>::iterator it;
    for(it=L1.begin(); it != L1.end(); ++it)
    {
        bool ok = false;
        for(iterator=L2.begin(); ok != true, iterator != L2.end(); ++iterator)
        {
            if((*it).exp == (*iterator).exp)
            {
                ok = true;
                pair<double, double> p;
                p.exp = (*it).exp;
                p.coef = (*it).coef + (*iterator).coef;
                if(p.coef != 0) rez.setElementPolinom(p);
            }
        }
        if(iterator == L2.end() && ok!=true)
        {
            pair<double, double> p;
            p.exp = (*it).exp;
            p.coef = (*it).coef;
            rez.setElementPolinom(p);
        }
    }

    for(iterator = L2.begin(); iterator != L2.end(); ++iterator)
    {
      bool ok = false;
      for(it=L1.begin(); ok != true, it != L1.end(); ++it)
      {
          if((*it).exp == (*iterator).exp) ok = true;
      }
      if(it == L1.end() && ok!=true)
      {
          pair<double, double> p;
          p.exp = (*iterator).exp;
          p.coef = (*iterator).coef;
          rez.setElementPolinom(p);
      }
    }

    rez.sortList();
    return rez;
}

Polinom Polinom::operator-(Polinom& aux)
{
    Polinom rez;
    list<pair<double, double>> L1 = (*this).getList();
    list<pair<double, double>> L2 = aux.getList();

    list<pair<double, double>>::iterator iterator;
    list<pair<double, double>>::iterator it;
    for(it=L1.begin(); it != L1.end(); ++it)
    {
        bool ok = false;
        for(iterator=L2.begin(); ok != true, iterator != L2.end(); ++iterator)
        {
            if((*it).exp == (*iterator).exp)
            {
                ok = true;
                pair<double, double> p;
                p.exp = (*it).exp;
                p.coef = (*it).coef - (*iterator).coef;
                if(p.coef != 0) rez.setElementPolinom(p);
            }
        }
        if(iterator == L2.end() && ok!=true)
        {
            pair<double, double> p;
            p.exp = (*it).exp;
            p.coef = (*it).coef;
            rez.setElementPolinom(p);
        }
    }

    for(iterator = L2.begin(); iterator != L2.end(); ++iterator)
    {
      bool ok = false;
      for(it=L1.begin(); ok != true, it != L1.end(); ++it)
      {
          if((*it).exp == (*iterator).exp) ok = true;
      }
      if(it == L1.end() && ok!=true)
      {
          pair<double, double> p;
          p.exp = (*iterator).exp;
          p.coef = (*iterator).coef;
          rez.setElementPolinom(p);
      }
    }

    rez.sortList();
    return rez;
}

Polinom Polinom::operator*(Polinom& aux)
{
    double expMax1=0.0, expMax2 = 0.0;
    Polinom rez_aux, rez;
    list<pair<double, double>> L1 = (*this).getList();
    list<pair<double, double>> L2 = aux.getList();

    list<pair<double, double>>::iterator iterator;
    list<pair<double, double>>::iterator it;

    for(it=L1.begin(); it != L1.end(); ++it)
    {
        for(iterator=L2.begin(); iterator != L2.end(); ++iterator)
        {
            pair<double, double> p;
            p.exp = (*it).exp + (*iterator).exp;
            p.coef = (*it).coef * (*iterator).coef;
            rez_aux.setElementPolinom(p);
            if((*it).exp > expMax2) expMax2 = (*it).exp;
        }
        if((*it).exp > expMax1) expMax1 = (*it).exp;
    }

    list<pair<double, double>> L3 = rez_aux.getList();
    for(int i = 1; i < expMax1*expMax2 + 1; i++)
    {
        pair<double, double> p;
        p.exp = -1;
        p.coef = 0;
        for(it=L3.begin(); it != L3.end(); ++it)
        {
            if(i == (*it).exp)
            {
                p.exp = i;
                p.coef += (*it).coef;
            }
        }
        if(p.exp != -1 && p.coef != 0) rez.setElementPolinom(p);
    }
    rez.sortList();
    return rez;
}

double Polinom::calcul(double x)
{
    cout <<"Rezultatul in punctul " << x << " este: ";
    double rez = 0.0;

    list<pair<double, double>> L = (*this).getList();
    list<pair<double, double>>::iterator it;
    for(it=L.begin(); it != L.end(); ++it)
        rez += (*it).coef*pow(x, (*it).exp);
    return rez;
}

int main()
{
    Pereche p;
    Polinom A, B, C;

    f>>A;
    cout << A;

    f >> B;
    cout << B;

    C = B + A;
    cout << C;

    C = A + B;
    cout << C;

    C = A - B;
    cout << C;

    C = B - A;
    cout << C;

    C = A * B;
    cout << C;

    cout << A.calcul(2);
    return 0;
}
