//
// Usage: root -b -q 'scanTrigReport.C(11)'
// Usage: root -b -q 'scanTrigReport.C(13)'

void scanTrigReport(int channel){

   std::map<int, std::string> trees;
   trees[11] = "elTrees";
   trees[13] = "muTrees";

   TFile *f1 = new TFile(Form("%s/treeEDBR_BulkGravToZZToZlepZhad_M-800.root", trees[channel].c_str()));
   TFile *f2 = new TFile(Form("%s/treeEDBR_BulkGravToZZToZlepZhad_M-1000.root",trees[channel].c_str()));
   TFile *f3 = new TFile(Form("%s/treeEDBR_BulkGravToZZToZlepZhad_M-1200.root",trees[channel].c_str()));
   TFile *f4 = new TFile(Form("%s/treeEDBR_BulkGravToZZToZlepZhad_M-1400.root",trees[channel].c_str()));
   TFile *f5 = new TFile(Form("%s/treeEDBR_BulkGravToZZToZlepZhad_M-1600.root",trees[channel].c_str()));
   TFile *f6 = new TFile(Form("%s/treeEDBR_BulkGravToZZToZlepZhad_M-1800.root",trees[channel].c_str()));
   TFile *f7 = new TFile(Form("%s/treeEDBR_BulkGravToZZToZlepZhad_M-2000.root",trees[channel].c_str()));
   TFile *f8 = new TFile(Form("%s/treeEDBR_BulkGravToZZToZlepZhad_M-2500.root",trees[channel].c_str()));
   TFile *f9 = new TFile(Form("%s/treeEDBR_BulkGravToZZToZlepZhad_M-3000.root",trees[channel].c_str()));
   TFile *fA = new TFile(Form("%s/treeEDBR_BulkGravToZZToZlepZhad_M-3500.root",trees[channel].c_str()));
   TFile *fB = new TFile(Form("%s/treeEDBR_BulkGravToZZToZlepZhad_M-4000.root",trees[channel].c_str()));
   TFile *fC = new TFile(Form("%s/treeEDBR_BulkGravToZZToZlepZhad_M-4500.root",trees[channel].c_str()));

   TTree *t1, *t2, *t3, *t4, *t5, *t6, *t7, *t8, *t9, *tA, *tB, *tC;

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

   int hlt1 = t1->GetEntries( Form("index>=6 && lep==%d", channel) );
   int hlt2 = t2->GetEntries( Form("index>=6 && lep==%d", channel) );
   int hlt3 = t3->GetEntries( Form("index>=6 && lep==%d", channel) );
   int hlt4 = t4->GetEntries( Form("index>=6 && lep==%d", channel) );
   int hlt5 = t5->GetEntries( Form("index>=6 && lep==%d", channel) );
   int hlt6 = t6->GetEntries( Form("index>=6 && lep==%d", channel) );
   int hlt7 = t7->GetEntries( Form("index>=6 && lep==%d", channel) );
   int hlt8 = t8->GetEntries( Form("index>=6 && lep==%d", channel) );
   int hlt9 = t9->GetEntries( Form("index>=6 && lep==%d", channel) );
   int hltA = tA->GetEntries( Form("index>=6 && lep==%d", channel) );
   int hltB = tB->GetEntries( Form("index>=6 && lep==%d", channel) );
   int hltC = tC->GetEntries( Form("index>=6 && lep==%d", channel) );

   int vtx1 = t1->GetEntries( Form("index>=19 && lep==%d", channel) );
   int vtx2 = t2->GetEntries( Form("index>=19 && lep==%d", channel) );
   int vtx3 = t3->GetEntries( Form("index>=19 && lep==%d", channel) );
   int vtx4 = t4->GetEntries( Form("index>=19 && lep==%d", channel) );
   int vtx5 = t5->GetEntries( Form("index>=19 && lep==%d", channel) );
   int vtx6 = t6->GetEntries( Form("index>=19 && lep==%d", channel) );
   int vtx7 = t7->GetEntries( Form("index>=19 && lep==%d", channel) );
   int vtx8 = t8->GetEntries( Form("index>=19 && lep==%d", channel) );
   int vtx9 = t9->GetEntries( Form("index>=19 && lep==%d", channel) );
   int vtxA = tA->GetEntries( Form("index>=19 && lep==%d", channel) );
   int vtxB = tB->GetEntries( Form("index>=19 && lep==%d", channel) );
   int vtxC = tC->GetEntries( Form("index>=19 && lep==%d", channel) );

   int lep1 = t1->GetEntries( Form("index>=20 && lep==%d", channel) );
   int lep2 = t2->GetEntries( Form("index>=20 && lep==%d", channel) );
   int lep3 = t3->GetEntries( Form("index>=20 && lep==%d", channel) );
   int lep4 = t4->GetEntries( Form("index>=20 && lep==%d", channel) );
   int lep5 = t5->GetEntries( Form("index>=20 && lep==%d", channel) );
   int lep6 = t6->GetEntries( Form("index>=20 && lep==%d", channel) );
   int lep7 = t7->GetEntries( Form("index>=20 && lep==%d", channel) );
   int lep8 = t8->GetEntries( Form("index>=20 && lep==%d", channel) );
   int lep9 = t9->GetEntries( Form("index>=20 && lep==%d", channel) );
   int lepA = tA->GetEntries( Form("index>=20 && lep==%d", channel) );
   int lepB = tB->GetEntries( Form("index>=20 && lep==%d", channel) );
   int lepC = tC->GetEntries( Form("index>=20 && lep==%d", channel) );

   int dil1 = t1->GetEntries( Form("index>=23 && lep==%d", channel) );
   int dil2 = t2->GetEntries( Form("index>=23 && lep==%d", channel) );
   int dil3 = t3->GetEntries( Form("index>=23 && lep==%d", channel) );
   int dil4 = t4->GetEntries( Form("index>=23 && lep==%d", channel) );
   int dil5 = t5->GetEntries( Form("index>=23 && lep==%d", channel) );
   int dil6 = t6->GetEntries( Form("index>=23 && lep==%d", channel) );
   int dil7 = t7->GetEntries( Form("index>=23 && lep==%d", channel) );
   int dil8 = t8->GetEntries( Form("index>=23 && lep==%d", channel) );
   int dil9 = t9->GetEntries( Form("index>=23 && lep==%d", channel) );
   int dilA = tA->GetEntries( Form("index>=23 && lep==%d", channel) );
   int dilB = tB->GetEntries( Form("index>=23 && lep==%d", channel) );
   int dilC = tC->GetEntries( Form("index>=23 && lep==%d", channel) );

   int jet1 = t1->GetEntries( Form("index>=26 && lep==%d", channel) );
   int jet2 = t2->GetEntries( Form("index>=26 && lep==%d", channel) );
   int jet3 = t3->GetEntries( Form("index>=26 && lep==%d", channel) );
   int jet4 = t4->GetEntries( Form("index>=26 && lep==%d", channel) );
   int jet5 = t5->GetEntries( Form("index>=26 && lep==%d", channel) );
   int jet6 = t6->GetEntries( Form("index>=26 && lep==%d", channel) );
   int jet7 = t7->GetEntries( Form("index>=26 && lep==%d", channel) );
   int jet8 = t8->GetEntries( Form("index>=26 && lep==%d", channel) );
   int jet9 = t9->GetEntries( Form("index>=26 && lep==%d", channel) );
   int jetA = tA->GetEntries( Form("index>=26 && lep==%d", channel) );
   int jetB = tB->GetEntries( Form("index>=26 && lep==%d", channel) );
   int jetC = tC->GetEntries( Form("index>=26 && lep==%d", channel) );

   int jes1 = t1->GetEntries( Form("index>=29 && lep==%d", channel) );
   int jes2 = t2->GetEntries( Form("index>=29 && lep==%d", channel) );
   int jes3 = t3->GetEntries( Form("index>=29 && lep==%d", channel) );
   int jes4 = t4->GetEntries( Form("index>=29 && lep==%d", channel) );
   int jes5 = t5->GetEntries( Form("index>=29 && lep==%d", channel) );
   int jes6 = t6->GetEntries( Form("index>=29 && lep==%d", channel) );
   int jes7 = t7->GetEntries( Form("index>=29 && lep==%d", channel) );
   int jes8 = t8->GetEntries( Form("index>=29 && lep==%d", channel) );
   int jes9 = t9->GetEntries( Form("index>=29 && lep==%d", channel) );
   int jesA = tA->GetEntries( Form("index>=29 && lep==%d", channel) );
   int jesB = tB->GetEntries( Form("index>=29 && lep==%d", channel) );
   int jesC = tC->GetEntries( Form("index>=29 && lep==%d", channel) );

   int gra1 = t1->GetEntries( Form("index>=30 && lep==%d", channel) );
   int gra2 = t2->GetEntries( Form("index>=30 && lep==%d", channel) );
   int gra3 = t3->GetEntries( Form("index>=30 && lep==%d", channel) );
   int gra4 = t4->GetEntries( Form("index>=30 && lep==%d", channel) );
   int gra5 = t5->GetEntries( Form("index>=30 && lep==%d", channel) );
   int gra6 = t6->GetEntries( Form("index>=30 && lep==%d", channel) );
   int gra7 = t7->GetEntries( Form("index>=30 && lep==%d", channel) );
   int gra8 = t8->GetEntries( Form("index>=30 && lep==%d", channel) );
   int gra9 = t9->GetEntries( Form("index>=30 && lep==%d", channel) );
   int graA = tA->GetEntries( Form("index>=30 && lep==%d", channel) );
   int graB = tB->GetEntries( Form("index>=30 && lep==%d", channel) );
   int graC = tC->GetEntries( Form("index>=30 && lep==%d", channel) );

   std::map<int, std::string> sufix;
   sufix[11] = "Elchannel";
   sufix[13] = "Muchannel";
   const char *outFile = Form("cutFlow_BulkGraviton_%s.txt",sufix[channel].c_str());
   std::ofstream ofs;
   ofs.open(outFile, std::ofstream::out);

   ofs << "******************************************";
   ofs << "******************************************************************************************************************\n";
   ofs << Form("*          *  %6s   *   %6s  *   %6s  *   %6s  *   %6s  *   %6s  *   %6s  *   %6s  *   %6s  *   %6s  *   %6s  *   %6s  *\n",\
                            "M-800","M-1000","M-1200","M-1400","M-1600","M-1800","M-2000","M-2500","M-3000","M-3500","M-4000","M-4500");
   ofs << "******************************************";
   ofs << "******************************************************************************************************************\n";
   ofs << Form("* Begin    *  %6d   *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *\n",\
                              beg1  ,  beg2  ,   beg3 ,   beg4 ,   beg5 ,   beg6 ,   beg7 ,   beg8 ,   beg9 ,   begA ,   begB ,   begC);
   ofs << Form("* HLT      *  %6d   *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *\n",\
                              hlt1  ,  hlt2  ,   hlt3 ,   hlt4 ,   hlt5 ,   hlt6 ,   hlt7 ,   hlt8 ,   hlt9 ,   hltA ,   hltB ,   hltC);
   ofs << Form("* Vertex   *  %6d   *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *\n",\
                              vtx1  ,  vtx2  ,   vtx3 ,   vtx4 ,   vtx5 ,   vtx6 ,   vtx7 ,   vtx8 ,   vtx9 ,   vtxA ,   vtxB ,   vtxC);
   ofs << Form("* Lepton   *  %6d   *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *\n",\
                              lep1  ,  lep2  ,   lep3 ,   lep4 ,   lep5 ,   lep6 ,   lep7 ,   lep8 ,   lep9 ,   lepA ,   lepB ,   lepC);
   ofs << Form("* Zpeak    *  %6d   *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *\n",\
                              dil1  ,  dil2  ,   dil3 ,   dil4 ,   dil5 ,   dil6 ,   dil7 ,   dil8 ,   dil9 ,   dilA ,   dilB ,   dilC);
   ofs << Form("* JetID    *  %6d   *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *\n",\
                              jet1  ,  jet2  ,   jet3 ,   jet4 ,   jet5 ,   jet6 ,   jet7 ,   jet8 ,   jet9 ,   jetA ,   jetB ,   jetC);
   ofs << Form("* JetMass  *  %6d   *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *\n",\
                              jes1  ,  jes2  ,   jes3 ,   jes4 ,   jes5 ,   jes6 ,   jes7 ,   jes8 ,   jes9 ,   jesA ,   jesB ,   jesC);
   ofs << Form("* Graviton *  %6d   *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *\n",\
                              gra1  ,  gra2  ,   gra3 ,   gra4 ,   gra5 ,   gra6 ,   gra7 ,   gra8 ,   gra9 ,   graA ,   graB ,   graC);
   ofs << "******************************************";
   ofs << "******************************************************************************************************************\n";

   ofs.close();

}
