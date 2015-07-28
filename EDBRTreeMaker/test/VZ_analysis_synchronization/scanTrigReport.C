//
// Usage: root -b -q 'scanTrigReport.C(11)'
// Usage: root -b -q 'scanTrigReport.C(13)'

void scanTrigReport(int channel){

   TFile *f0 = new TFile("treeEDBR_BulkGravToZZToZlepZhad_M-600.root");
   TFile *f1 = new TFile("treeEDBR_BulkGravToZZToZlepZhad_M-800.root");
   TFile *f2 = new TFile("treeEDBR_BulkGravToZZToZlepZhad_M-1000.root");
   TFile *f3 = new TFile("treeEDBR_BulkGravToZZToZlepZhad_M-1200.root");
   TFile *f4 = new TFile("treeEDBR_BulkGravToZZToZlepZhad_M-1400.root");
   TFile *f5 = new TFile("treeEDBR_BulkGravToZZToZlepZhad_M-1600.root");
   TFile *f6 = new TFile("treeEDBR_BulkGravToZZToZlepZhad_M-1800.root");
   TFile *f7 = new TFile("treeEDBR_BulkGravToZZToZlepZhad_M-2000.root");
   TFile *f8 = new TFile("treeEDBR_BulkGravToZZToZlepZhad_M-2500.root");
   TFile *f9 = new TFile("treeEDBR_BulkGravToZZToZlepZhad_M-3000.root");
   TFile *fA = new TFile("treeEDBR_BulkGravToZZToZlepZhad_M-3500.root");
   TFile *fB = new TFile("treeEDBR_BulkGravToZZToZlepZhad_M-4000.root");
   TFile *fC = new TFile("treeEDBR_BulkGravToZZToZlepZhad_M-4500.root");

   TTree *t0, *t1, *t2, *t3, *t4, *t5, *t6, *t7, *t8, *t9, *tA, *tB, *tC;

   f0->GetObject("trigReport/genTree", t0);
   f1->GetObject("trigReport/genTree", t1);
   f2->GetObject("trigReport/genTree", t2);
   f3->GetObject("trigReport/genTree", t3);
   f4->GetObject("trigReport/genTree", t4);
   f5->GetObject("trigReport/genTree", t5);
   f6->GetObject("trigReport/genTree", t6);
   f7->GetObject("trigReport/genTree", t7);
   f8->GetObject("trigReport/genTree", t8);
   f9->GetObject("trigReport/genTree", t9);
   fA->GetObject("trigReport/genTree", tA);
   fB->GetObject("trigReport/genTree", tB);
   fC->GetObject("trigReport/genTree", tC);
 
   int beg0 = t0->GetEntries( Form("index>=2 && lep==%d", channel) );
   int beg1 = t1->GetEntries( Form("index>=2 && lep==%d", channel) );
   int beg2 = t2->GetEntries( Form("index>=2 && lep==%d", channel) );
   int beg3 = t3->GetEntries( Form("index>=2 && lep==%d", channel) );
   int beg4 = t4->GetEntries( Form("index>=2 && lep==%d", channel) );
   int beg5 = t5->GetEntries( Form("index>=2 && lep==%d", channel) );
   int beg6 = t6->GetEntries( Form("index>=2 && lep==%d", channel) );
   int beg7 = t7->GetEntries( Form("index>=2 && lep==%d", channel) );
   int beg8 = t8->GetEntries( Form("index>=2 && lep==%d", channel) );
   int beg9 = t9->GetEntries( Form("index>=2 && lep==%d", channel) );
   int begA = tA->GetEntries( Form("index>=2 && lep==%d", channel) );
   int begB = tB->GetEntries( Form("index>=2 && lep==%d", channel) );
   int begC = tC->GetEntries( Form("index>=2 && lep==%d", channel) );

   int hlt0 = t0->GetEntries( Form("index>=5 && lep==%d", channel) );
   int hlt1 = t1->GetEntries( Form("index>=5 && lep==%d", channel) );
   int hlt2 = t2->GetEntries( Form("index>=5 && lep==%d", channel) );
   int hlt3 = t3->GetEntries( Form("index>=5 && lep==%d", channel) );
   int hlt4 = t4->GetEntries( Form("index>=5 && lep==%d", channel) );
   int hlt5 = t5->GetEntries( Form("index>=5 && lep==%d", channel) );
   int hlt6 = t6->GetEntries( Form("index>=5 && lep==%d", channel) );
   int hlt7 = t7->GetEntries( Form("index>=5 && lep==%d", channel) );
   int hlt8 = t8->GetEntries( Form("index>=5 && lep==%d", channel) );
   int hlt9 = t9->GetEntries( Form("index>=5 && lep==%d", channel) );
   int hltA = tA->GetEntries( Form("index>=5 && lep==%d", channel) );
   int hltB = tB->GetEntries( Form("index>=5 && lep==%d", channel) );
   int hltC = tC->GetEntries( Form("index>=5 && lep==%d", channel) );

   int vtx0 = t0->GetEntries( Form("index>=12 && lep==%d", channel) );
   int vtx1 = t1->GetEntries( Form("index>=12 && lep==%d", channel) );
   int vtx2 = t2->GetEntries( Form("index>=12 && lep==%d", channel) );
   int vtx3 = t3->GetEntries( Form("index>=12 && lep==%d", channel) );
   int vtx4 = t4->GetEntries( Form("index>=12 && lep==%d", channel) );
   int vtx5 = t5->GetEntries( Form("index>=12 && lep==%d", channel) );
   int vtx6 = t6->GetEntries( Form("index>=12 && lep==%d", channel) );
   int vtx7 = t7->GetEntries( Form("index>=12 && lep==%d", channel) );
   int vtx8 = t8->GetEntries( Form("index>=12 && lep==%d", channel) );
   int vtx9 = t9->GetEntries( Form("index>=12 && lep==%d", channel) );
   int vtxA = tA->GetEntries( Form("index>=12 && lep==%d", channel) );
   int vtxB = tB->GetEntries( Form("index>=12 && lep==%d", channel) );
   int vtxC = tC->GetEntries( Form("index>=12 && lep==%d", channel) );

   int lep0 = t0->GetEntries( Form("index>=13 && lep==%d", channel) );
   int lep1 = t1->GetEntries( Form("index>=13 && lep==%d", channel) );
   int lep2 = t2->GetEntries( Form("index>=13 && lep==%d", channel) );
   int lep3 = t3->GetEntries( Form("index>=13 && lep==%d", channel) );
   int lep4 = t4->GetEntries( Form("index>=13 && lep==%d", channel) );
   int lep5 = t5->GetEntries( Form("index>=13 && lep==%d", channel) );
   int lep6 = t6->GetEntries( Form("index>=13 && lep==%d", channel) );
   int lep7 = t7->GetEntries( Form("index>=13 && lep==%d", channel) );
   int lep8 = t8->GetEntries( Form("index>=13 && lep==%d", channel) );
   int lep9 = t9->GetEntries( Form("index>=13 && lep==%d", channel) );
   int lepA = tA->GetEntries( Form("index>=13 && lep==%d", channel) );
   int lepB = tB->GetEntries( Form("index>=13 && lep==%d", channel) );
   int lepC = tC->GetEntries( Form("index>=13 && lep==%d", channel) );

   int dil0 = t0->GetEntries( Form("index>=17 && lep==%d", channel) );
   int dil1 = t1->GetEntries( Form("index>=17 && lep==%d", channel) );
   int dil2 = t2->GetEntries( Form("index>=17 && lep==%d", channel) );
   int dil3 = t3->GetEntries( Form("index>=17 && lep==%d", channel) );
   int dil4 = t4->GetEntries( Form("index>=17 && lep==%d", channel) );
   int dil5 = t5->GetEntries( Form("index>=17 && lep==%d", channel) );
   int dil6 = t6->GetEntries( Form("index>=17 && lep==%d", channel) );
   int dil7 = t7->GetEntries( Form("index>=17 && lep==%d", channel) );
   int dil8 = t8->GetEntries( Form("index>=17 && lep==%d", channel) );
   int dil9 = t9->GetEntries( Form("index>=17 && lep==%d", channel) );
   int dilA = tA->GetEntries( Form("index>=17 && lep==%d", channel) );
   int dilB = tB->GetEntries( Form("index>=17 && lep==%d", channel) );
   int dilC = tC->GetEntries( Form("index>=17 && lep==%d", channel) );

   int jet0 = t0->GetEntries( Form("index>=19 && lep==%d", channel) );
   int jet1 = t1->GetEntries( Form("index>=19 && lep==%d", channel) );
   int jet2 = t2->GetEntries( Form("index>=19 && lep==%d", channel) );
   int jet3 = t3->GetEntries( Form("index>=19 && lep==%d", channel) );
   int jet4 = t4->GetEntries( Form("index>=19 && lep==%d", channel) );
   int jet5 = t5->GetEntries( Form("index>=19 && lep==%d", channel) );
   int jet6 = t6->GetEntries( Form("index>=19 && lep==%d", channel) );
   int jet7 = t7->GetEntries( Form("index>=19 && lep==%d", channel) );
   int jet8 = t8->GetEntries( Form("index>=19 && lep==%d", channel) );
   int jet9 = t9->GetEntries( Form("index>=19 && lep==%d", channel) );
   int jetA = tA->GetEntries( Form("index>=19 && lep==%d", channel) );
   int jetB = tB->GetEntries( Form("index>=19 && lep==%d", channel) );
   int jetC = tC->GetEntries( Form("index>=19 && lep==%d", channel) );

   int gra0 = t0->GetEntries( Form("index>=20 && lep==%d", channel) );
   int gra1 = t1->GetEntries( Form("index>=20 && lep==%d", channel) );
   int gra2 = t2->GetEntries( Form("index>=20 && lep==%d", channel) );
   int gra3 = t3->GetEntries( Form("index>=20 && lep==%d", channel) );
   int gra4 = t4->GetEntries( Form("index>=20 && lep==%d", channel) );
   int gra5 = t5->GetEntries( Form("index>=20 && lep==%d", channel) );
   int gra6 = t6->GetEntries( Form("index>=20 && lep==%d", channel) );
   int gra7 = t7->GetEntries( Form("index>=20 && lep==%d", channel) );
   int gra8 = t8->GetEntries( Form("index>=20 && lep==%d", channel) );
   int gra9 = t9->GetEntries( Form("index>=20 && lep==%d", channel) );
   int graA = tA->GetEntries( Form("index>=20 && lep==%d", channel) );
   int graB = tB->GetEntries( Form("index>=20 && lep==%d", channel) );
   int graC = tC->GetEntries( Form("index>=20 && lep==%d", channel) );

   std::map<int, std::string> sufix;
   sufix[11] = "Elchannel";
   sufix[13] = "Muchannel";
   const char *outFile = Form("cutFlow_BulkGraviton_%s.txt",sufix[channel].c_str());
   std::ofstream ofs;
   ofs.open(outFile, std::ofstream::out);

   ofs << "*****************************************************";
   ofs << "******************************************************************************************************************\n";
   ofs << Form("*          *  %6s  *  %6s   *   %6s  *   %6s  *   %6s  *   %6s  *   %6s  *   %6s  *   %6s  *   %6s  *   %6s  *   %6s  *   %6s  *\n",\
                            "M-600", "M-800","M-1000","M-1200","M-1400","M-1600","M-1800","M-2000","M-2500","M-3000","M-3500","M-4000","M-4500");
   ofs << "*****************************************************";
   ofs << "******************************************************************************************************************\n";
   ofs << Form("* Begin    *  %6d  *  %6d   *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *\n",\
                              beg0 ,  beg1  ,  beg2  ,   beg3 ,   beg4 ,   beg5 ,   beg6 ,   beg7 ,   beg8 ,   beg9 ,   begA ,   begB ,   begC);
   ofs << Form("* HLT      *  %6d  *  %6d   *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *\n",\
                              hlt0 ,  hlt1  ,  hlt2  ,   hlt3 ,   hlt4 ,   hlt5 ,   hlt6 ,   hlt7 ,   hlt8 ,   hlt9 ,   hltA ,   hltB ,   hltC);
   ofs << Form("* Vertex   *  %6d  *  %6d   *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *\n",\
                              vtx0 ,  vtx1  ,  vtx2  ,   vtx3 ,   vtx4 ,   vtx5 ,   vtx6 ,   vtx7 ,   vtx8 ,   vtx9 ,   vtxA ,   vtxB ,   vtxC);
   ofs << Form("* Lepton   *  %6d  *  %6d   *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *\n",\
                              lep0 ,  lep1  ,  lep2  ,   lep3 ,   lep4 ,   lep5 ,   lep6 ,   lep7 ,   lep8 ,   lep9 ,   lepA ,   lepB ,   lepC);
   ofs << Form("* Dilepton *  %6d  *  %6d   *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *\n",\
                              dil0 ,  dil1  ,  dil2  ,   dil3 ,   dil4 ,   dil5 ,   dil6 ,   dil7 ,   dil8 ,   dil9 ,   dilA ,   dilB ,   dilC);
   ofs << Form("* V-jet    *  %6d  *  %6d   *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *\n",\
                              jet0 ,  jet1  ,  jet2  ,   jet3 ,   jet4 ,   jet5 ,   jet6 ,   jet7 ,   jet8 ,   jet9 ,   jetA ,   jetB ,   jetC);
   ofs << Form("* Graviton *  %6d  *  %6d   *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *\n",\
                              gra0 ,  gra1  ,  gra2  ,   gra3 ,   gra4 ,   gra5 ,   gra6 ,   gra7 ,   gra8 ,   gra9 ,   graA ,   graB ,   graC);
   ofs << "*****************************************************";
   ofs << "******************************************************************************************************************\n";

   ofs.close();

}
