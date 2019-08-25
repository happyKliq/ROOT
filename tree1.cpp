#include <TRandom.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <Riostream.h>


using namespace std;

//class TObject

class Det : public TObject //каждый детектор дает сигнал энергии и времени
{
public:

  Double_t e;
  Double_t t;
};

class Event: public TObject
{
public:
  Det a;  
  Det b;
  ClassDef(Event, 1);
};

ClassImp(Event)

void tree0 ()
{
  TTree * tree = new TTree ("tree", "treelibrated tree");
  Event * e = new Event;

  //создаем ветвь события
  tree-> Branch("event", &e);

  //заполняем события рандомными числами в цикле
  Int_t nenevt = 10000;
  for (Int_t iev=0; iev < nenevt; iev++)
  {
    if (iev%1000==0) cout<<"Processing event "<<iev<<"..."<<endl;

    Float_t ea, eb;
    gRandom -> Rannor(ea, eb); //две энергии и распреедление Гаусса
     e -> a.e = ea;
     e -> b.e = eb;
     e -> a.t = gRandom -> Rndm();
     e -> b.t = ev -> a.t + gRandom -> Gaus (0.,.1);
     tree -> Fill(); //заполняем дерево текущими событиями
  }

  //исследуем структуру класса
  tree -> StartViewer();
  //gRoot -> SetStyle("Plain");


TCanvas *c1 = new TCanvas();
c1  -> Divide(2,2);
c1 -> cd(1);

tree -> Draw("a.e");
tree -> Draw("a.e", "3*(-.2<b.e && b.e <.2)", "same");  
c1 -> cd(2);

tree -> Draw("b.e:a.e", "", "colz"); 
c1 -> cd(3);


tree -> Draw("b.t", "", "e");  
tree -> Draw("a.t", "", "same");  
c1 -> cd(4);
tree -> Draw("b.t:a.t");
cout<<endl;
cout<<"U can now examine the structure of your tree in the TreeViewer"<<endl;

cout<<endl;
}
