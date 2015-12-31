//
// Usage: root -b -q 'scanTrigReport.C(11)'
// Usage: root -b -q 'scanTrigReport.C(13)'

void scanTrigReport(int channel){

   std::map<int, std::string> trees;
   trees[11] = "elChannel";
   trees[13] = "muChannel";

   std::map<int, int> kin;
   kin[11] =  9;
   kin[13] = 12;

   TFile *f1 = new TFile(Form("trees/treeEDBR_BulkGravToZZToZlepZhad_M-800_%s.root", trees[channel].c_str()));
   TFile *f2 = new TFile(Form("trees/treeEDBR_BulkGravToZZToZlepZhad_M-1000_%s.root",trees[channel].c_str()));
   TFile *f3 = new TFile(Form("trees/treeEDBR_BulkGravToZZToZlepZhad_M-1200_%s.root",trees[channel].c_str()));
   TFile *f4 = new TFile(Form("trees/treeEDBR_BulkGravToZZToZlepZhad_M-1400_%s.root",trees[channel].c_str()));
   TFile *f5 = new TFile(Form("trees/treeEDBR_BulkGravToZZToZlepZhad_M-1600_%s.root",trees[channel].c_str()));
   TFile *f6 = new TFile(Form("trees/treeEDBR_BulkGravToZZToZlepZhad_M-1800_%s.root",trees[channel].c_str()));
   TFile *f7 = new TFile(Form("trees/treeEDBR_BulkGravToZZToZlepZhad_M-2000_%s.root",trees[channel].c_str()));
   TFile *f8 = new TFile(Form("trees/treeEDBR_BulkGravToZZToZlepZhad_M-2500_%s.root",trees[channel].c_str()));
   TFile *f9 = new TFile(Form("trees/treeEDBR_BulkGravToZZToZlepZhad_M-3000_%s.root",trees[channel].c_str()));
   TFile *fA = new TFile(Form("trees/treeEDBR_BulkGravToZZToZlepZhad_M-3500_%s.root",trees[channel].c_str()));
   TFile *fB = new TFile(Form("trees/treeEDBR_BulkGravToZZToZlepZhad_M-4000_%s.root",trees[channel].c_str()));
   TFile *fC = new TFile(Form("trees/treeEDBR_BulkGravToZZToZlepZhad_M-4500_%s.root",trees[channel].c_str()));

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
 
   int beg1 = t1->GetEntries( "index" );
   int beg2 = t2->GetEntries( "index" );
   int beg3 = t3->GetEntries( "index" );
   int beg4 = t4->GetEntries( "index" );
   int beg5 = t5->GetEntries( "index" );
   int beg6 = t6->GetEntries( "index" );
   int beg7 = t7->GetEntries( "index" );
   int beg8 = t8->GetEntries( "index" );
   int beg9 = t9->GetEntries( "index" );
   int begA = tA->GetEntries( "index" );
   int begB = tB->GetEntries( "index" );
   int begC = tC->GetEntries( "index" );

   int hlt1 = t1->GetEntries( "index>1" );
   int hlt2 = t2->GetEntries( "index>1" );
   int hlt3 = t3->GetEntries( "index>1" );
   int hlt4 = t4->GetEntries( "index>1" );
   int hlt5 = t5->GetEntries( "index>1" );
   int hlt6 = t6->GetEntries( "index>1" );
   int hlt7 = t7->GetEntries( "index>1" );
   int hlt8 = t8->GetEntries( "index>1" );
   int hlt9 = t9->GetEntries( "index>1" );
   int hltA = tA->GetEntries( "index>1" );
   int hltB = tB->GetEntries( "index>1" );
   int hltC = tC->GetEntries( "index>1" );

   int vtx1 = t1->GetEntries( "index>4" );
   int vtx2 = t2->GetEntries( "index>4" );
   int vtx3 = t3->GetEntries( "index>4" );
   int vtx4 = t4->GetEntries( "index>4" );
   int vtx5 = t5->GetEntries( "index>4" );
   int vtx6 = t6->GetEntries( "index>4" );
   int vtx7 = t7->GetEntries( "index>4" );
   int vtx8 = t8->GetEntries( "index>4" );
   int vtx9 = t9->GetEntries( "index>4" );
   int vtxA = tA->GetEntries( "index>4" );
   int vtxB = tB->GetEntries( "index>4" );
   int vtxC = tC->GetEntries( "index>4" );

   int kin1 = t1->GetEntries( Form("index>%d", kin[channel])   );
   int kin2 = t2->GetEntries( Form("index>%d", kin[channel])   );
   int kin3 = t3->GetEntries( Form("index>%d", kin[channel])   );
   int kin4 = t4->GetEntries( Form("index>%d", kin[channel])   );
   int kin5 = t5->GetEntries( Form("index>%d", kin[channel])   );
   int kin6 = t6->GetEntries( Form("index>%d", kin[channel])   );
   int kin7 = t7->GetEntries( Form("index>%d", kin[channel])   );
   int kin8 = t8->GetEntries( Form("index>%d", kin[channel])   );
   int kin9 = t9->GetEntries( Form("index>%d", kin[channel])   );
   int kinA = tA->GetEntries( Form("index>%d", kin[channel])   );
   int kinB = tB->GetEntries( Form("index>%d", kin[channel])   );
   int kinC = tC->GetEntries( Form("index>%d", kin[channel])   );

   int ids1 = t1->GetEntries( Form("index>%d", kin[channel]+1) );
   int ids2 = t2->GetEntries( Form("index>%d", kin[channel]+1) );
   int ids3 = t3->GetEntries( Form("index>%d", kin[channel]+1) );
   int ids4 = t4->GetEntries( Form("index>%d", kin[channel]+1) );
   int ids5 = t5->GetEntries( Form("index>%d", kin[channel]+1) );
   int ids6 = t6->GetEntries( Form("index>%d", kin[channel]+1) );
   int ids7 = t7->GetEntries( Form("index>%d", kin[channel]+1) );
   int ids8 = t8->GetEntries( Form("index>%d", kin[channel]+1) );
   int ids9 = t9->GetEntries( Form("index>%d", kin[channel]+1) );
   int idsA = tA->GetEntries( Form("index>%d", kin[channel]+1) );
   int idsB = tB->GetEntries( Form("index>%d", kin[channel]+1) );
   int idsC = tC->GetEntries( Form("index>%d", kin[channel]+1) );

   int iso1 = t1->GetEntries( Form("index>%d", kin[channel]+2) );
   int iso2 = t2->GetEntries( Form("index>%d", kin[channel]+2) );
   int iso3 = t3->GetEntries( Form("index>%d", kin[channel]+2) );
   int iso4 = t4->GetEntries( Form("index>%d", kin[channel]+2) );
   int iso5 = t5->GetEntries( Form("index>%d", kin[channel]+2) );
   int iso6 = t6->GetEntries( Form("index>%d", kin[channel]+2) );
   int iso7 = t7->GetEntries( Form("index>%d", kin[channel]+2) );
   int iso8 = t8->GetEntries( Form("index>%d", kin[channel]+2) );
   int iso9 = t9->GetEntries( Form("index>%d", kin[channel]+2) );
   int isoA = tA->GetEntries( Form("index>%d", kin[channel]+2) );
   int isoB = tB->GetEntries( Form("index>%d", kin[channel]+2) );
   int isoC = tC->GetEntries( Form("index>%d", kin[channel]+2) );

   int dau1 = t1->GetEntries( "index>18" );
   int dau2 = t2->GetEntries( "index>18" );
   int dau3 = t3->GetEntries( "index>18" );
   int dau4 = t4->GetEntries( "index>18" );
   int dau5 = t5->GetEntries( "index>18" );
   int dau6 = t6->GetEntries( "index>18" );
   int dau7 = t7->GetEntries( "index>18" );
   int dau8 = t8->GetEntries( "index>18" );
   int dau9 = t9->GetEntries( "index>18" );
   int dauA = tA->GetEntries( "index>18" );
   int dauB = tB->GetEntries( "index>18" );
   int dauC = tC->GetEntries( "index>18" );

   int dch1 = t1->GetEntries( "index>19" );
   int dch2 = t2->GetEntries( "index>19" );
   int dch3 = t3->GetEntries( "index>19" );
   int dch4 = t4->GetEntries( "index>19" );
   int dch5 = t5->GetEntries( "index>19" );
   int dch6 = t6->GetEntries( "index>19" );
   int dch7 = t7->GetEntries( "index>19" );
   int dch8 = t8->GetEntries( "index>19" );
   int dch9 = t9->GetEntries( "index>19" );
   int dchA = tA->GetEntries( "index>19" );
   int dchB = tB->GetEntries( "index>19" );
   int dchC = tC->GetEntries( "index>19" );

   int dil1 = t1->GetEntries( "index>20" );
   int dil2 = t2->GetEntries( "index>20" );
   int dil3 = t3->GetEntries( "index>20" );
   int dil4 = t4->GetEntries( "index>20" );
   int dil5 = t5->GetEntries( "index>20" );
   int dil6 = t6->GetEntries( "index>20" );
   int dil7 = t7->GetEntries( "index>20" );
   int dil8 = t8->GetEntries( "index>20" );
   int dil9 = t9->GetEntries( "index>20" );
   int dilA = tA->GetEntries( "index>20" );
   int dilB = tB->GetEntries( "index>20" );
   int dilC = tC->GetEntries( "index>20" );

   int gen1 = t1->GetEntries( "index>22" );
   int gen2 = t2->GetEntries( "index>22" );
   int gen3 = t3->GetEntries( "index>22" );
   int gen4 = t4->GetEntries( "index>22" );
   int gen5 = t5->GetEntries( "index>22" );
   int gen6 = t6->GetEntries( "index>22" );
   int gen7 = t7->GetEntries( "index>22" );
   int gen8 = t8->GetEntries( "index>22" );
   int gen9 = t9->GetEntries( "index>22" );
   int genA = tA->GetEntries( "index>22" );
   int genB = tB->GetEntries( "index>22" );
   int genC = tC->GetEntries( "index>22" );

   int jid1 = t1->GetEntries( "index>24" );
   int jid2 = t2->GetEntries( "index>24" );
   int jid3 = t3->GetEntries( "index>24" );
   int jid4 = t4->GetEntries( "index>24" );
   int jid5 = t5->GetEntries( "index>24" );
   int jid6 = t6->GetEntries( "index>24" );
   int jid7 = t7->GetEntries( "index>24" );
   int jid8 = t8->GetEntries( "index>24" );
   int jid9 = t9->GetEntries( "index>24" );
   int jidA = tA->GetEntries( "index>24" );
   int jidB = tB->GetEntries( "index>24" );
   int jidC = tC->GetEntries( "index>24" );

   int jet1 = t1->GetEntries( "index>26" );
   int jet2 = t2->GetEntries( "index>26" );
   int jet3 = t3->GetEntries( "index>26" );
   int jet4 = t4->GetEntries( "index>26" );
   int jet5 = t5->GetEntries( "index>26" );
   int jet6 = t6->GetEntries( "index>26" );
   int jet7 = t7->GetEntries( "index>26" );
   int jet8 = t8->GetEntries( "index>26" );
   int jet9 = t9->GetEntries( "index>26" );
   int jetA = tA->GetEntries( "index>26" );
   int jetB = tB->GetEntries( "index>26" );
   int jetC = tC->GetEntries( "index>26" );

   int jek1 = t1->GetEntries( "index>28" );
   int jek2 = t2->GetEntries( "index>28" );
   int jek3 = t3->GetEntries( "index>28" );
   int jek4 = t4->GetEntries( "index>28" );
   int jek5 = t5->GetEntries( "index>28" );
   int jek6 = t6->GetEntries( "index>28" );
   int jek7 = t7->GetEntries( "index>28" );
   int jek8 = t8->GetEntries( "index>28" );
   int jek9 = t9->GetEntries( "index>28" );
   int jekA = tA->GetEntries( "index>28" );
   int jekB = tB->GetEntries( "index>28" );
   int jekC = tC->GetEntries( "index>28" );

   int gra1 = t1->GetEntries( "index>31" );
   int gra2 = t2->GetEntries( "index>31" );
   int gra3 = t3->GetEntries( "index>31" );
   int gra4 = t4->GetEntries( "index>31" );
   int gra5 = t5->GetEntries( "index>31" );
   int gra6 = t6->GetEntries( "index>31" );
   int gra7 = t7->GetEntries( "index>31" );
   int gra8 = t8->GetEntries( "index>31" );
   int gra9 = t9->GetEntries( "index>31" );
   int graA = tA->GetEntries( "index>31" );
   int graB = tB->GetEntries( "index>31" );
   int graC = tC->GetEntries( "index>31" );

   std::map<int, std::string> sufix;
   sufix[11] = "elchannel";
   sufix[13] = "muchannel";
   const char *outFile = Form("cutFlow_BulkGraviton_%s.txt",sufix[channel].c_str());
   std::ofstream ofs;
   ofs.open(outFile, std::ofstream::out);

   ofs << "********************************************";
   ofs << "******************************************************************************************************************\n";
   ofs << Form("*            *  %6s   *   %6s  *   %6s  *   %6s  *   %6s  *   %6s  *   %6s  *   %6s  *   %6s  *   %6s  *   %6s  *   %6s  *\n",\
                              "M-800" ,"M-1000","M-1200","M-1400","M-1600","M-1800","M-2000","M-2500","M-3000","M-3500","M-4000","M-4500");
   ofs << "********************************************";
   ofs << "******************************************************************************************************************\n";
   ofs << Form("* AllEvts    *  %6d   *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *\n",\
                               50000  , 48400  ,  49200 ,  50000 ,  50000 ,  50000 ,  50000 ,  50000 ,  49200 ,  50000 ,  50000 ,  50000);
   ofs << Form("* GenZlep    *  %6d   *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *\n",\
                                beg1  ,  beg2  ,   beg3 ,   beg4 ,   beg5 ,   beg6 ,   beg7 ,   beg8 ,   beg9 ,   begA ,   begB ,   begC);
   ofs << Form("* HLT        *  %6d   *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *\n",\
                                hlt1  ,  hlt2  ,   hlt3 ,   hlt4 ,   hlt5 ,   hlt6 ,   hlt7 ,   hlt8 ,   hlt9 ,   hltA ,   hltB ,   hltC);
   ofs << Form("* Vertex     *  %6d   *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *\n",\
                                vtx1  ,  vtx2  ,   vtx3 ,   vtx4 ,   vtx5 ,   vtx6 ,   vtx7 ,   vtx8 ,   vtx9 ,   vtxA ,   vtxB ,   vtxC);
   ofs << Form("* LeptonKin  *  %6d   *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *\n",\
                                kin1  ,  kin2  ,   kin3 ,   kin4 ,   kin5 ,   kin6 ,   kin7 ,   kin8 ,   kin9 ,   kinA ,   kinB ,   kinC);
   ofs << Form("* LeptonID   *  %6d   *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *\n",\
                                ids1  ,  ids2  ,   ids3 ,   ids4 ,   ids5 ,   ids6 ,   ids7 ,   ids8 ,   ids9 ,   idsA ,   idsB ,   idsC);
   ofs << Form("* LeptonIso  *  %6d   *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *\n",\
                                iso1  ,  iso2  ,   iso3 ,   iso4 ,   iso5 ,   iso6 ,   iso7 ,   iso8 ,   iso9 ,   isoA ,   isoB ,   isoC);
   ofs << Form("* Zdaughter  *  %6d   *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *\n",\
                                dau1  ,  dau2  ,   dau3 ,   dau4 ,   dau5 ,   dau6 ,   dau7 ,   dau8 ,   dau9 ,   dauA ,   dauB ,   dauC);
   ofs << Form("* ZdauCharge *  %6d   *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *\n",\
                                dch1  ,  dch2  ,   dch3 ,   dch4 ,   dch5 ,   dch6 ,   dch7 ,   dch8 ,   dch9 ,   dchA ,   dchB ,   dchC);
   ofs << Form("* Zpeak      *  %6d   *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *\n",\
                                dil1  ,  dil2  ,   dil3 ,   dil4 ,   dil5 ,   dil6 ,   dil7 ,   dil8 ,   dil9 ,   dilA ,   dilB ,   dilC);
   ofs << Form("* GenZhad    *  %6d   *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *\n",\
                                gen1  ,  gen2  ,   gen3 ,   gen4 ,   gen5 ,   gen6 ,   gen7 ,   gen8 ,   gen9 ,   genA ,   genB ,   genC);
   ofs << Form("* JetID      *  %6d   *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *\n",\
                                jid1  ,  jid2  ,   jid3 ,   jid4 ,   jid5 ,   jid6 ,   jid7 ,   jid8 ,   jid9 ,   jidA ,   jidB ,   jidC);
   ofs << Form("* JetClean   *  %6d   *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *\n",\
                                jet1  ,  jet2  ,   jet3 ,   jet4 ,   jet5 ,   jet6 ,   jet7 ,   jet8 ,   jet9 ,   jetA ,   jetB ,   jetC);
   ofs << Form("* JetKin     *  %6d   *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *\n",\
                                jek1  ,  jek2  ,   jek3 ,   jek4 ,   jek5 ,   jek6 ,   jek7 ,   jek8 ,   jek9 ,   jekA ,   jekB ,   jekC);
   ofs << Form("* Graviton   *  %6d   *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *   %6d  *\n",\
                                gra1  ,  gra2  ,   gra3 ,   gra4 ,   gra5 ,   gra6 ,   gra7 ,   gra8 ,   gra9 ,   graA ,   graB ,   graC);
   ofs << "********************************************";
   ofs << "******************************************************************************************************************\n";

   ofs.close();

}
