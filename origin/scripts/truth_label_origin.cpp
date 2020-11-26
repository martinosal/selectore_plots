/*
root [1] .L ../plots/origin/scripts/truth_label_origin.cpp
root [2] derivedtruthlabel("trk_origin_truth_label_B",_file0)
*/

void truthlabel(std::string hist,TFile* fData=_file0){
  TH1F* h = (TH1F*)fData->Get(hist.c_str());//truth label origin
  const Int_t nbins = h->GetNbinsX();
  const TAxis *axis_x=h->GetXaxis();
  const Int_t x_min=axis_x->GetXmin(); // should be -1 relative to i = 1;

  std::vector<int> origin_truth_label={0,1,2,3,4,5,6,11,12,13,14,15,16,101,102,103,104,105,106,111,112,113,114,115,116};
  int y=0;
  for(std::vector<int>::iterator it = origin_truth_label.begin(); it != origin_truth_label.end(); ++it){
    y=h->GetBinContent(*it+2);
    std::cout<<"truth label "<<*it<<":\t"<<y<<"\n";
  }
}

void derivedtruthlabel(std::string hist,TFile* fData=_file0){
  TH1F* h = (TH1F*)fData->Get(hist.c_str());//truth label origin
  const Int_t nbins = h->GetNbinsX();
  const TAxis *axis_x=h->GetXaxis();
  const Int_t x_min=axis_x->GetXmin(); // should be -1 relative to i = 1;

  std::vector<int> truthlabel={0,1,2,3,4,5,6,11,12,13,14,15,16,101,102,103,104,105,106,111,112,113,114,115,116};//25 categories
  std::vector<int> derived_truthlabel={0,1,2,3,4,5};

  std::vector<int> map_0={0};
  std::vector<int> map_1={2,4,6};
  std::vector<int> map_2={12,14,16,102,104,106,112,114,116};
  std::vector<int> map_3={1,11,101,111};
  std::vector<int> map_4={3,5};
  std::vector<int> map_5={13,103,113,15,105,115};

  std::vector<std::vector<int>> list;
  list.push_back(map_0);
    list.push_back(map_1);
      list.push_back(map_2);
        list.push_back(map_3);
          list.push_back(map_4);
            list.push_back(map_5);



  int y=0;

  for(int i=0;i<list.size();i++){
    y=0;
    for(std::vector<int>::iterator it = list.at(i).begin(); it != list.at(i).end(); ++it){
      y+=h->GetBinContent(*it+2);
    }
    std::cout<<"derived truth label "<<i<<":\t"<<y<<"\n";
  }
}

void eff_truthlabel(std::string hist_num,std::string hist_den,TFile* fData=_file0){
  TH1F* h_num = (TH1F*)fData->Get(hist_num.c_str());//truth label origin - num
  TH1F* h_den = (TH1F*)fData->Get(hist_den.c_str());//truth label origin - den
  const Int_t nbins = h_num->GetNbinsX();
  const TAxis *axis_x=h_num->GetXaxis();
  const Int_t x_min=axis_x->GetXmin(); // should be -1 relative to i = 1;

  std::vector<int> origin_truth_label={0,1,2,3,4,5,6,11,12,13,14,15,16,101,102,103,104,105,106,111,112,113,114,115,116};
  int y_num=0,y_den=0;
  for(std::vector<int>::iterator it = origin_truth_label.begin(); it != origin_truth_label.end(); ++it){
    y_num=h_num->GetBinContent(*it+2);
    y_den=h_den->GetBinContent(*it+2);
    std::cout<<"truth label "<<*it<<":\t"<<y_num<<"\t"<<y_den<<"\t"<<"acceptance: "<<(float) y_num/y_den<<"\n";
  }
}

void eff_derivedtruthlabel(std::string hist_num,std::string hist_den,TFile* fData=_file0){
  TH1F* h_num = (TH1F*)fData->Get(hist_num.c_str());//truth label origin - num
  TH1F* h_den = (TH1F*)fData->Get(hist_den.c_str());//truth label origin - den
  const Int_t nbins = h_num->GetNbinsX();
  const TAxis *axis_x=h_num->GetXaxis();
  const Int_t x_min=axis_x->GetXmin(); // should be -1 relative to i = 1;

  std::vector<int> truthlabel={0,1,2,3,4,5,6,11,12,13,14,15,16,101,102,103,104,105,106,111,112,113,114,115,116};//25 categories
  std::vector<int> derived_truthlabel={0,1,2,3,4,5};

  std::vector<int> map_0={0};
  std::vector<int> map_1={2,4,6};
  std::vector<int> map_2={12,14,16,102,104,106,112,114,116};
  std::vector<int> map_3={1,11,101,111};
  std::vector<int> map_4={3,5};
  std::vector<int> map_5={13,103,113,15,105,115};

  std::vector<std::vector<int>> list;
  list.push_back(map_0);
    list.push_back(map_1);
      list.push_back(map_2);
        list.push_back(map_3);
          list.push_back(map_4);
            list.push_back(map_5);



  int y_num=0,y_den=0;

  for(int i=0;i<list.size();i++){
    y_num=0,y_den=0;
//    std::cout<<list.at(i).size()<<"\n";
//    std::vector
    for(std::vector<int>::iterator it = list.at(i).begin(); it != list.at(i).end(); ++it){
//      std::cout<<*it<<"\t";
      y_num+=h_num->GetBinContent(*it+2);
      y_den+=h_den->GetBinContent(*it+2);
    }
    std::cout<<"truth label origin "<<i<<":\t"<<y_num<<"\t"<<y_den<<"\t"<<"acceptance: "<<(float) y_num/y_den<<"\n";
  }
}


void jet_orig(std::string hist,TFile* fData=_file0, int DpT=50, double pt_max=1000){

  TH2F* h = (TH2F*)fData->Get(hist.c_str());
  const Int_t n_Xbins = h->GetNbinsX();
  const Int_t n_Ybins = h->GetNbinsY();
  const double y_max = h->GetYaxis()->GetXmax();

//  int DpT=100;
  double bin_to_pT=(double) n_Ybins/y_max;
  int rebin=(int) DpT/bin_to_pT;
  int Nbins=(int) pt_max/DpT;

  double M[Nbins][n_Xbins];
  double M_der[Nbins][7];


  TCanvas c("c", "canvas", 1300, 900);
  c.SetGrid();

  gPad->SetLogy();

  TH1D** px = new TH1D*[Nbins];
  for(int k=0;k<Nbins;k++){
    TString sx=Form("hj%d",k);
    px[k] = h->ProjectionX(sx,bin_to_pT*DpT*k,bin_to_pT*DpT*(k+1));
    px[k]->SetStats(0);
    float N=px[k]->GetEntries();
    px[k]->Scale(1./N);
    std::string s = std::to_string(k);
    std::string s1 = std::to_string((int) DpT*k);
    std::string s2 = std::to_string((int) DpT*(k+1));
    px[k]->SetTitle(("origin trk in ["+s1+","+s2+"] Gev jet pT").c_str());
//    px[k]->Draw("hist");
//    c.SaveAs(("/home/salomon/Private/atlas/FTPF/Selector/plots/origin/"+hist+"Xproj_"+s+".pdf").c_str());
    for(int i=1;i<=n_Xbins;i++){
      M[k][i]=px[k]->GetBinContent(i);
//      std::cout<<M[k][i]<<"\t";
    }
    std::cout<<"\n";
  }

  std::vector<int> truthlabel={0,1,2,3,4,5,6,11,12,13,14,15,16,101,102,103,104,105,106,111,112,113,114,115,116};//25 categories
  std::vector<int> derived_truthlabel={0,1,2,3,4,5};

  std::vector<int> map_0={0};
  std::vector<int> map_1={2,4,6};
  std::vector<int> map_2={12,14,16,102,104,106,112,114,116};
  std::vector<int> map_3={1,11,101,111};
  std::vector<int> map_4={3,5};
  std::vector<int> map_5={13,103,113,15,105,115};

  std::vector<std::vector<int>> list;
  list.push_back(map_0);
    list.push_back(map_1);
      list.push_back(map_2);
        list.push_back(map_3);
          list.push_back(map_4);
            list.push_back(map_5);

  float y=0;

  for(int k=0;k<Nbins;k++){
    std::cout<<"\ntrk in ["<<DpT*k<<","<<DpT*(k+1)<<"] Gev jet pT";
    for(int i=0;i<list.size();i++){
      y=0;
      std::cout<<"\norigin: "<<i<<"\t";
      for(std::vector<int>::iterator it = list.at(i).begin(); it != list.at(i).end(); ++it){
//        std::cout<<*it<<" "<<M[k][*it+2]<<"\t";
        y+=M[k][*it+2];
      }
      std::cout<<y<<"\t";
      M_der[k][i+1]=y;
    }
  }
/*
  for(int i=1;i<=8;i++){
    std::cout<<"\n";
    for(int k=0;k<Nbins;k++){
      std::cout<<M_der[k][i]<<"\t";
  }
}
*/
  string origin[6] = {"PU","FAKE","FAKE_b/c","GEANT","FRAG","B/C"};
  int colors[6] = {2,30,38,44,12,4};

  auto leg = new TLegend(0.2,0.2,0.35,0.4);//x1,y1,x2,y2
  TH1D** py_2 = new TH1D*[n_Xbins];
  for(int i=1;i<=6;i++){
    py_2[i] = new TH1D(Form("syj%d",i),"",Nbins,0,pt_max);
    for(int k=0;k<Nbins;k++){
      py_2[i]->AddBinContent(k+1,M_der[k][i]);
      py_2[i]->SetStats(0);
      py_2[i]->GetYaxis()->SetRangeUser(1e-3, 1.);
      py_2[i]->GetXaxis()->SetTitle("jet pT [GeV]");
      py_2[i]->GetYaxis()->SetTitle("fraction of tracks");
      py_2[i]->SetLineWidth(2);
      py_2[i]->SetLineColor(colors[i-1]);
      py_2[i]->SetOption("col");
      py_2[i]->SetMarkerStyle(5);
      py_2[i]->SetMarkerSize(2);
    }
    leg->AddEntry(py_2[i],origin[i-1].c_str(),"l");
      py_2[i]->Draw("same hist");
      py_2[i]->Draw("hist p same");
  }
    leg->Draw();
    c.SaveAs(("/home/salomon/Private/atlas/FTPF/Selector/plots/origin/"+hist+"_binN.pdf").c_str());
    delete h,M,c,px,py_2;
}

void avtrk_orig(std::string hist,std::string hist_jet_pt,TFile* fData=_file0, int DpT=50, double pt_max=1000){

  TH2F* h = (TH2F*)fData->Get(hist.c_str());
  TH1F* h_jet = (TH1F*)fData->Get(hist_jet_pt.c_str());
  const Int_t n_Xbins = h->GetNbinsX();
  const Int_t n_Ybins = h->GetNbinsY();
  const Int_t y_max = h->GetYaxis()->GetXmax();
  const Int_t n_bins_jet = h_jet->GetNbinsX();
  const double pt_max_jet = h_jet->GetXaxis()->GetXmax();

  if(n_bins_jet!=n_Ybins || y_max!=pt_max_jet)  std::cout<<"ERROR\n";

//  int DpT=100;
  double bin_to_pT=(double) n_Ybins/y_max;
  std::cout<<bin_to_pT<<"\n";
  int rebin=bin_to_pT*DpT;//nbins associated with DpT
  int Nbins=(int) pt_max/DpT;

  TCanvas c("c", "canvas", 1300, 900);
  c.SetGrid();
  gPad->SetLogy();

  TH1* jet_pt=h_jet->RebinX(rebin,"jet_pt");

  double M[Nbins][n_Xbins];
  double M_der[Nbins][7];

  std::cout<<n_Ybins<<", "<<pt_max<<", "<<Nbins<<"\n";
  std::cout<<n_bins_jet<<", "<<pt_max_jet<<", "<<Nbins<<"\n";


  TH1D** px = new TH1D*[Nbins];
  for(int k=0;k<Nbins;k++){
    TString sx=Form("hj%d",k);
    px[k] = h->ProjectionX(sx,bin_to_pT*DpT*k,bin_to_pT*DpT*(k+1));
    px[k]->SetStats(0);
//    float N=px[k]->GetEntries();
//    px[k]->Scale(1./N);
    std::string s = std::to_string(k);
    std::string s1 = std::to_string((int) DpT*k);
    std::string s2 = std::to_string((int) DpT*(k+1));
    px[k]->SetTitle(("origin trk in ["+s1+","+s2+"] Gev jet pT").c_str());
//    px[k]->Draw("hist");
//    c.SaveAs(("/home/salomon/Private/atlas/FTPF/Selector/plots/origin/"+hist+"Xproj_"+s+".pdf").c_str());
    for(int i=1;i<=n_Xbins;i++){
      M[k][i]=px[k]->GetBinContent(i);
//      std::cout<<M[k][i]<<"\t";
    }
  }

  std::vector<int> truthlabel={0,1,2,3,4,5,6,11,12,13,14,15,16,101,102,103,104,105,106,111,112,113,114,115,116};//25 categories
  std::vector<int> derived_truthlabel={0,1,2,3,4,5};

  std::vector<int> map_0={0};
  std::vector<int> map_1={2,4,6};
  std::vector<int> map_2={12,14,16,102,104,106,112,114,116};
  std::vector<int> map_3={1,11,101,111};
  std::vector<int> map_4={3,5};
  std::vector<int> map_5={13,103,113,15,105,115};

  std::vector<std::vector<int>> list;
  list.push_back(map_0);
    list.push_back(map_1);
      list.push_back(map_2);
        list.push_back(map_3);
          list.push_back(map_4);
            list.push_back(map_5);

  float y=0;

  for(int k=0;k<Nbins;k++){
    for(int i=0;i<list.size();i++){
      y=0;
//      std::cout<<"\norigin: "<<i<<"\t";
      for(std::vector<int>::iterator it = list.at(i).begin(); it != list.at(i).end(); ++it){
//        std::cout<<*it<<" "<<M[k][*it+2]<<"\t";
        y+=M[k][*it+2];
      }
//      std::cout<<"sum: "<<y<<"\t";
      M_der[k][i+1]=y;
    }
  }
/*
  for(int i=1;i<=8;i++){
    std::cout<<"\n";
    for(int k=0;k<Nbins;k++){
      std::cout<<M_der[k][i]<<"\t";
  }
}
*/
  string origin[6] = {"PU","FAKE","FAKE_b/c","GEANT","FRAG","B/C"};
  int colors[6] = {2,30,38,44,12,4};

  auto leg = new TLegend(0.75,0.75,0.9,0.9);//x1,y1,x2,y2
//  auto leg = new TLegend(0.75,0.15,0.85,0.35);//x1,y1,x2,y2
  TH1D** py_2 = new TH1D*[n_Xbins];
  for(int i=1;i<=6;i++){
    py_2[i] = new TH1D(Form("sya%d",i),"",Nbins,0,pt_max);
    for(int k=0;k<Nbins;k++){
      py_2[i]->AddBinContent(k+1,M_der[k][i]);
    }
  }
/*
  for(int i=1;i<=6;i++){
    std::cout<<"\n";
    for(int k=0;k<Nbins;k++){
      std::cout<<M_der[k][i]<<"\t";
    }
  }
*/
//  TH1D *h2 = new TH1D("h","efficiency_vs_jetpT",Nbins,0,pt_max);
//  h2=(TH1D*)jet_pt->Clone();
  TH1D** h2 = new TH1D*[6];
  double jetpt_bin=0.;
  double avtrk=0.,error=0.;

  for(int i=1;i<=6;i++){
    h2[i]= new TH1D(Form("h2a%d",i),"",Nbins,0,pt_max);
    for(int k=0;k<Nbins;k++){
      jetpt_bin=(double) jet_pt->GetBinContent(k+1);
      avtrk= (double) M_der[k][i]/jetpt_bin;
      h2[i]->AddBinContent(k+1,avtrk);
//      std::cout<<M[k][i]<<"\t"<<jetpt_bin<<"\t"<<avtrk<<"\n";
    }
  }
  for(int k=0;k<Nbins;k++){
    std::cout<<"\ntrk in ["<<DpT*k<<","<<DpT*(k+1)<<"] Gev jet pT";
    for(int i=1;i<=6;i++){
      std::cout<<"\norigin: "<<i<<"\t";
      avtrk=(double) h2[i]->GetBinContent(k+1);
      jetpt_bin=(double) jet_pt->GetBinContent(k+1);
      error=(double) abs(1./jetpt_bin-M_der[k][i]/(jetpt_bin*jetpt_bin));
      std::cout<<avtrk<<"   \t+- "<<error;
    }
  }
  std::cout<<"\n";

  for(int i=1;i<=6;i++){
    h2[i]->SetStats(0);
    h2[i]->GetYaxis()->SetRangeUser(1e-2, 100);
    h2[i]->GetXaxis()->SetTitle("jet pT [GeV]");
    h2[i]->GetYaxis()->SetTitle("<trk>");
    h2[i]->SetLineWidth(2);
    h2[i]->SetLineColor(colors[i-1]);
    h2[i]->SetOption("col");
    h2[i]->SetMarkerStyle(5);
    h2[i]->SetMarkerSize(2);
    leg->AddEntry(h2[i],origin[i-1].c_str(),"l");
    h2[i]->Draw("same hist");
    h2[i]->Draw("hist p same");
  }

  leg->Draw();
  c.SaveAs(("/home/salomon/Private/atlas/FTPF/Selector/plots/origin/"+hist+"_"+hist_jet_pt+"_avtracks.pdf").c_str());

  delete h,h2,M,c,px,py_2;
}
