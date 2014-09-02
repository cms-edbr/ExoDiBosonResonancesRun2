#include "TMathText.h"

TMathText* makeCMSPreliminaryURC(int energy = 7, double x = 0.67, double y = 0.85) {
  char buffer[256];
  sprintf(buffer,"CMS Preliminary");
  TMathText* tex = new TMathText(x,y,buffer);
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(0.04);
  tex->Draw();

  sprintf(buffer,"\\sqrt{s} = %i TeV",energy);
  tex = new TMathText(x,y-0.05,buffer);
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(0.04);
  tex->Draw();
  return tex;
}

TMathText* makeCMSFinalURC(int energy = 7, double x = 0.67, double y = 0.85) {
  char buffer[256];
  sprintf(buffer,"CMS");
  TMathText* tex = new TMathText(x,y,buffer);
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(0.04);
  tex->Draw();

  sprintf(buffer,"\\sqrt{s} = %i TeV",energy);
  tex = new TMathText(x,y-0.05,buffer);
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(0.04);
  tex->Draw();
  return tex;
}

/*
TMathText* makeCMSFinalTop(int energy = 7, double x = 0.15, double y = 0.94) {
  char buffer[256];
  sprintf(buffer,"CMS        \\sqrt{s} = %i TeV",energy);
  TMathText* tex = new TMathText(x,y,buffer);
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->Draw();
  return tex;
}
*/
TMathText* makeCMSFinalTop(double x = 0.15, double y = 0.94) {
  char buffer[256];
  sprintf(buffer,"CMS ");
  TMathText* tex = new TMathText(x,y,buffer);
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->Draw();
  return tex;
}



TMathText* makeCMSPreliminaryTop(int energy = 7, double x = 0.15, double y = 0.94) {
  char buffer[256];
  sprintf(buffer,"\\hbox{CMS Preliminary  }\\sqrt{s}\\hbox{ = %i TeV}",energy);
  TMathText* tex = new TMathText(x,y,buffer);
  tex->SetNDC();
  tex->SetTextFont(42);
  //tex->SetTextSize(0.04);
  tex->Draw();
  return tex;
}

/*
TMathText* makeCMSLumi(double lumi = 5.0, double x = 0.666, double y = 0.72) {
  char buffer[256];
  sprintf(buffer,"\\int L dt = %4.1lf fb^{-1}",lumi);
  TMathText* tex = new TMathText(x,y,buffer);
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(0.030);
  tex->Draw();
  return tex;
}
*/
TMathText* makeCMSLumi(int energy = 7,double lumi = 5.0, double x = 0.666, double y = 0.72) {
  char buffer[256];
  sprintf(buffer,"\\sqrt{s} = %i TeV,  \\int L dt = %4.1lf fb^{-1}",energy,lumi);
  TMathText* tex = new TMathText(x,y,buffer);
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(0.030);
  tex->Draw();
  return tex;
}

TMathText* makeChannelLabel(int nJets, int flavour, bool isZZchannel, double x = 0.75, double y = 0.94) {
  char buffer[256];
  char c;
  if(nJets==1)
    c='1';
  if(nJets==2)
    c='2';
  if(nJets==-1)
    c='X';

  if(flavour == 0 && isZZchannel == true)
    sprintf(buffer,"2\\ell %c\\hbox{j channel}",c);
  if(flavour == 0 && isZZchannel == false)
    sprintf(buffer,"\\ell\\nu %c\\hbox{j channel}",c);
  if(flavour == 11 && isZZchannel == true)
    sprintf(buffer,"2e %c\\hbox{j channel}",c);
  if(flavour == 13 && isZZchannel == true)
    sprintf(buffer,"2\\mu %c\\hbox{j channel}",c);
  if(flavour == 11 && isZZchannel == false)
    sprintf(buffer,"e\\nu_{e} %c\\hbox{j channel}",c);
  if(flavour == 13 && isZZchannel == false)
    sprintf(buffer,"\\mu\\nu_{\\mu} %c\\hbox{j channel}",c);
  TMathText* tex = new TMathText(x,y,buffer);
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(0.04);
  tex->Draw();
  return tex;
}
