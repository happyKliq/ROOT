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
  Det a; //there are 2 detectors in the experiment
  Det b;
  ClassDef(Event, 1);
};

ClassImp(Event)

void tree0 ()
{
  TTree * tree = new TTree ("tree", "treelibrated tree");
  Event * e = new Event;

  //create a Branch
  tree-> Branch("event", &e);

  //fill some events with random numbers

  Int_t nenevt = 10000;
  for (Int_t iev=0; iev < nevent; iev++)
  {
    if (iev%1000==0) cout<<"Processing event "<<iev<<"..."<<endl;

    Float_t ea, eb;
    gRandom -> Rannor(ea, eb); //"две энергии"" дают распреедление Гаусса
     e -> a.e = ea;
     e -> b.e = eb;
     e -> a.t = gRandom -> Rndm();
     e -> b.t = ev -> a.t + gRandom -> Gaus (0.,.1);
     tree -> Fill(); //заполнил дерево текущими событиями
  }

  //исследуем структуру класса

  tree -> StartViewer();
  //gRoot -> SetStyle("Plain");

  //now we can feel us painters
TCanvas *c1 = new TCanvas();
c1  -> Divide(2,2);
c1 -> cd(1);

tree -> Draw("a.e");
tree -> Draw("a.e", "3*(-.2<b.e && b.e <.2)", "same"); //то же самое, но с условием для энергии b;
//масштабируется на 3
c1 -> cd(2);

tree -> Draw("b.e:a.e", "", "colz"); // одна энергия против другой
c1 -> cd(3);


tree -> Draw("b.t", "", "e"); //time of b with errorbars
tree -> Draw("a.t", "", "same"); //время детектора а
c1 -> cd(4);
tree -> Draw("b.t:a.t");
cout<<endl;
cout<<"U can now examine the structure of your tree in the TreeViewer"<<endl;

cout<<endl;
}
