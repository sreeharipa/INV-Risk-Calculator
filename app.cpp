#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <vector>
#include <cmath>
using namespace std;



class Riskcalc
{
public: 
    vector<float> arms, cf, vdv, karms; 
    float exposure, aeight, vdveight, eav, elv;
    int domax;
    char choice;
    void getinput();
    void viewinput();
    void sumfactormultiply();
    void domaxis();
    void riskiso();
    void eavelv();
    void riskacgih();
    float round(float);
    Riskcalc()
    {
        getinput();
        cout<<"Do you want to view the entered data?(y/n)"<<endl;
        cin>>choice;
        if((choice == 'y') || (choice == 'Y'))
        {
            viewinput();
        }
        sumfactormultiply();
        domaxis();
        eavelv();
        riskiso();
        riskacgih();
        system("pause");
    } 

};

float Riskcalc::round(float var)
{
    // 37.66666 * 100 =3766.66
    // 3766.66 + .5 =3767.16    for rounding off value
    // then type cast to int so value is 3767
    // then divided by 100 so the value converted into 37.67
    float value = (int)(var * 100 + .5);
    return (float)value / 100;
}

void Riskcalc::getinput()
{
    float input;
    cout<<"Enter the following data"<<endl;
    cout<<"RMS acceleration in 3 axes (x, y, z respectively in ms^(-2)):"<<endl;
    for(int i = 0; i<3; i++)
    {
        
        cin>>input;
        arms.push_back(input);
        
    }
    cout<<"Estimated duration of exposure in a day (Hours):"<<endl;
    cin>>exposure;
    cout<<"Linear Crest Factor in all three axes (x, y, z respectively):"<<endl;
    for(int i = 0; i<3; i++)
    {
        
        cin>>input;
        cf.push_back(input);
        
    }
    cout<<"VDV in all three axes (x, y, z respectively in ms-1.75):"<<endl;
    for(int i = 0; i<3; i++)
    {
        
        cin>>input;
        vdv.push_back(input);

    }
    
}


void Riskcalc::viewinput()
{
    cout<<"Entered data is as follows: "<<endl;
    cout<<"RMS acceleration in 3 axes: "<<endl;
    for(int i = 0; i<3; i++)
    {
        cout<<arms[i]<<endl;
    }    
    cout<<"Linear Crest Factor in all three axes:"<<endl;
    for(int i = 0; i<3; i++)
    {
        cout<<cf[i]<<endl;
    }
    cout<<"VDV in all three axes:"<<endl;
    for(int i = 0; i<3; i++)
    {
        cout<<vdv[i]<<endl;
    }
    cout<<"Estimated duration of exposure in a day (Hours):"<<endl;
    cout<<exposure<<endl;  
}

void Riskcalc::sumfactormultiply()
{
    float input;
    for(int i = 0; i<3; i++)
    {
        if(i == 2)
        {
            input = arms[i];
            karms.push_back(input);
        }
            
        else
        {
            input = arms[i]*1.4;
            karms.push_back(input);
        }    

    }


    cout<<"Weighted acceleration after multiplying by sum factor: "<<endl;
    for(int i = 0; i<3; i++)
    {
        cout<<round(karms[i])<<endl;
    }


}

void Riskcalc::domaxis()
{
    int max = 0;
    for(int i=1; i<3; i++)
    {
        if(karms[max]<karms[i])
        {
            max = i;
        }
    }

    if(max == 0)
    {
        cout<<"Dominant axis is the x axis"<<endl;
    }
    if(max == 1)
    {
        cout<<"Dominant axis is the y axis"<<endl;
    }
    if(max == 2)
    {
        cout<<"Dominant axis is the z axis"<<endl;
    }  
    cout<<"The rms acceleration in the dominant axis is "<<arms[max]<<" which after multiplying by sum factor becomes "<<round(karms[max])<<endl;
    domax = max;
    

         
}

void Riskcalc::eavelv()
{
    eav = (pow(0.5, 2)*8)/pow(karms[domax], 2);
    elv = (pow(1.15, 2)*8)/pow(karms[domax], 2);
    cout<<"Time to reach EAV (As per ACGIH Standards): "<<round(eav)<<" hrs"<<endl;
    cout<<"Time to reach ELV (As per ACGIH Standards): "<<round(elv)<<" hrs"<<endl;
    aeight = sqrt((pow(karms[domax], 2)*exposure)/8);
    cout<<"A(8) value for the given data is "<<round(aeight)<<endl;
    vdveight = pow(((pow(vdv[domax], 4)*exposure)/8), 1.0/4);
    cout<<"VDV(8) value for the given data is "<<round(vdveight)<<endl;

}

void Riskcalc::riskacgih()
{
    if (cf[domax]>9)
    {
        if (vdveight >= 17)
        {
            cout<<"The data shows high risk by ACGIH norms"<<endl;
        }
        else if (vdveight <= 8.5)
        {
            cout<<"The data shows minimal risk by ACGIH norms"<<endl;
        }
        else 
        {
            cout<<"The data shows moderate risk by ACGIH norms"<<endl;
        }
    }
    else
    {
        if (aeight>1.15)
        {
            cout<<"The data shows high risk by ACGIH norms"<<endl;
        }
        else if (aeight<0.50)
        {
            cout<<"The data shows minimal risk by ACGIH norms"<<endl;
        }
        else 
        {
            cout<<"The data shows moderate risk by ACGIH norms"<<endl;
        }
    }   
}

void Riskcalc::riskiso()
{
    if (cf[domax]>9)
    {
        if (vdveight >= 17)
        {
            cout<<"The data shows high risk by ISO norms"<<endl;
        }
        else if (vdveight <= 8.5)
        {
            cout<<"The data shows minimal risk by ISO norms"<<endl;
        }
        else 
        {
            cout<<"The data shows moderate risk by ISO norms"<<endl;
        }
    }
    else
    {
        if (aeight>0.87)
        {
            cout<<"The data shows high risk by ISO norms"<<endl;
        }
        else if (aeight<0.43)
        {
            cout<<"The data shows minimal risk by ISO norms"<<endl;
        }
        else 
        {
            cout<<"The data shows moderate risk by ISO norms"<<endl;
        }
    }   

}

int main()
{
    char x = 'y';
    
    while((x=='y')||(x=='Y'))
    {
        Riskcalc obj;
        cout<<"Do you want to enter more data? (y/n)"<<endl;
        cin>>x;

    }
    system("pause");
    
}