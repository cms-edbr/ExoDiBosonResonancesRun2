root -b << EOF
gSystem->Load("PDFs/HWWLVJRooPdfs_cxx.so")
.x countAnalysis.C( "MHP",  600,  400,  800 )
EOF

root -b << EOF
gSystem->Load("PDFs/HWWLVJRooPdfs_cxx.so")
.x countAnalysis.C( "MHP",  800,  600,  1000 )
EOF

root -b << EOF
gSystem->Load("PDFs/HWWLVJRooPdfs_cxx.so")
.x countAnalysis.C( "MHP", 1000,  800,  1200 )
EOF

root -b << EOF
gSystem->Load("PDFs/HWWLVJRooPdfs_cxx.so")
.x countAnalysis.C( "MHP", 1200,  1000,  1400 )
EOF

root -b << EOF
gSystem->Load("PDFs/HWWLVJRooPdfs_cxx.so")
.x countAnalysis.C( "MHP", 1400,  1200,  1600 )
EOF

root -b << EOF
gSystem->Load("PDFs/HWWLVJRooPdfs_cxx.so")
.x countAnalysis.C( "MHP", 1600,  1300,  1900 )
EOF

root -b << EOF
gSystem->Load("PDFs/HWWLVJRooPdfs_cxx.so")
.x countAnalysis.C( "MHP", 1800,  1500,  2100 )
EOF

root -b << EOF
gSystem->Load("PDFs/HWWLVJRooPdfs_cxx.so")
.x countAnalysis.C( "MHP", 2000,  1700,  2300 )
EOF

root -b << EOF
gSystem->Load("PDFs/HWWLVJRooPdfs_cxx.so")
.x countAnalysis.C( "MHP", 2500,  2100,  2900 )
EOF

root -b << EOF
gSystem->Load("PDFs/HWWLVJRooPdfs_cxx.so")
.x countAnalysis.C( "MHP", 3000,  2400,  3500 )
EOF

root -b << EOF
gSystem->Load("PDFs/HWWLVJRooPdfs_cxx.so")
.x countAnalysis.C( "MHP", 3500,  2900,  4000 )
EOF

root -b << EOF
gSystem->Load("PDFs/HWWLVJRooPdfs_cxx.so")
.x countAnalysis.C( "MHP", 4000,  3200,  4800 )
EOF

root -b << EOF
gSystem->Load("PDFs/HWWLVJRooPdfs_cxx.so")
.x countAnalysis.C( "MHP", 4500,  3700,  5300 )
EOF
