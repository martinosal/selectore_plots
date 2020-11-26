//Example of usage:
//.L ../plots/origin/scripts/truth_label_eff.cpp
//eff_derivedtruthlabel_jetpt("trk_jet_pT_origin_truth_label_JF_B","Bjet_cut_origin_truth_label_pT",_file0,100,400) <--- obsolete!
//eff_derivedtruthlabel_jetpt("SV1","Bjet_cut_origin_truth_label_pT",_file0,100,400)

void eff_derivedtruthlabel_jetpt(std::string alg,std::string hist_den="Bjet_cut_origin_truth_label_pT",TFile* fData=_file0, int DpT=50, double pt_max=1000){

  TH2F* h_num = (TH2F*)fData->Get(("trk_jet_pT_origin_truth_label_"+alg+"_B").c_str());//truth label origin - num
  TH2F* h_den = (TH2F*)fData->Get(hist_den.c_str());//truth label origin - den
  const Int_t n_Xbins_num = h_num->GetNbinsX();
  const Int_t n_Ybins_num = h_num->GetNbinsY();
  const TAxis *axis_xnum=h_num->GetXaxis();
  const TAxis *axis_ynum=h_num->GetYaxis();
  const Int_t xnum_min=axis_xnum->GetXmin(); // should be -1 relative to i = 1;
  const Int_t xnum_max=axis_xnum->GetXmax();
  const Int_t ynum_min=axis_ynum->GetXmin(); // should be -1 relative to i = 1;
  const Int_t ynum_max=axis_ynum->GetXmax();
  const Int_t n_Xbins_den = h_den->GetNbinsX();
  const Int_t n_Ybins_den = h_den->GetNbinsY();
  const TAxis *axis_xden=h_den->GetXaxis();
  const TAxis *axis_yden=h_den->GetYaxis();
  const Int_t xden_min=axis_xden->GetXmin(); // should be -1 relative to i = 1;
  const Int_t xden_max=axis_xden->GetXmax();
  const Int_t yden_min=axis_yden->GetXmin(); // should be -1 relative to i = 1;
  const Int_t yden_max=axis_yden->GetXmax();

  if(n_Xbins_num!=n_Xbins_den || n_Ybins_num!=n_Ybins_den || xnum_min!=xden_min || xnum_max!=xden_max){
    std::cout<<"Warning\n";
    return;
  }
  else{
    const Int_t n_Xbins=n_Xbins_num;
    const Int_t n_Ybins=n_Ybins_num;
    const Int_t x_min=xnum_min;
    const Int_t x_max=xnum_max;
    const Int_t y_min=ynum_min;
    const Int_t y_max=ynum_max;
    double bin_to_pT=(double) n_Ybins/y_max;
    std::cout<<bin_to_pT<<"\n";
    std::cout<<"\nn_Xbins: "<<n_Xbins<<"\tn_Ybins: "<<n_Ybins<<"\tx_min: "<<x_min<<"\tx_max: "<<x_max<<"\n";

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


    int Nbins=(int) pt_max/(DpT);

    double M_num[Nbins][n_Xbins],M_den[Nbins][n_Xbins];
    double M_num_der[Nbins][7],M_den_der[Nbins][7];

    std::cout<<"\nNumerator: "<<alg.c_str()<<"_b-jet composition\n";
    TH1D** px_num = new TH1D*[Nbins];
    for(int k=0;k<Nbins;k++){
      TString sx=Form("hj%d",k);
      px_num[k] = h_num->ProjectionX(sx,bin_to_pT*DpT*k,bin_to_pT*DpT*(k+1));
      px_num[k]->SetStats(0);
      std::string s = std::to_string(k);
      std::string s1 = std::to_string((int) DpT*k);
      std::string s2 = std::to_string((int) DpT*(k+1));
      px_num[k]->SetTitle(("origin trk in ["+s1+","+s2+"] Gev jet pT").c_str());
  //    px[k]->Draw("hist");
  //    c.SaveAs(("/home/salomon/Private/atlas/FTPF/Selector/plots/origin/"+hist+"Xproj_"+s+".pdf").c_str());
      for(int i=1;i<=n_Xbins;i++){
        M_num[k][i]=px_num[k]->GetBinContent(i);
  //      std::cout<<M[k][i]<<"\t";
      }
  //    std::cout<<"\n";
    }

    float y_num=0;
    for(int k=0;k<Nbins;k++){
      std::cout<<"\ntrk in ["<<DpT*k<<","<<DpT*(k+1)<<"] Gev jet pT";
      for(int i=0;i<list.size();i++){
        y_num=0;
        std::cout<<"\norigin: "<<i<<"\t";
        for(std::vector<int>::iterator it = list.at(i).begin(); it != list.at(i).end(); ++it){
  //        std::cout<<*it<<" "<<M_num[k][*it+2]<<"\t";
          y_num+=M_num[k][*it+2];
        }
        std::cout<<y_num;
        M_num_der[k][i+1]=y_num;
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

    std::cout<<"\n\nDenominator: "<<hist_den.c_str()<<"\n";
    TH1D** px_den = new TH1D*[Nbins];
    for(int k=0;k<Nbins;k++){
      TString sx=Form("hj%d",k);
      px_den[k] = h_den->ProjectionX(sx,bin_to_pT*DpT*k,bin_to_pT*DpT*(k+1));
      px_den[k]->SetStats(0);
      std::string s = std::to_string(k);
      std::string s1 = std::to_string((int) DpT*k);
      std::string s2 = std::to_string((int) DpT*(k+1));
      px_den[k]->SetTitle(("origin trk in ["+s1+","+s2+"] Gev jet pT").c_str());
  //    px[k]->Draw("hist");
  //    c.SaveAs(("/home/salomon/Private/atlas/FTPF/Selector/plots/origin/"+hist+"Xproj_"+s+".pdf").c_str());
      for(int i=1;i<=n_Xbins;i++){
        M_den[k][i]=px_den[k]->GetBinContent(i);
  //      std::cout<<M[k][i]<<"\t";
      }
  //    std::cout<<"\n";
    }

    double y_den=0.;
    double error=0.;
    for(int k=0;k<Nbins;k++){
      std::cout<<"\ntrk in ["<<DpT*k<<","<<DpT*(k+1)<<"] Gev jet pT";
      for(int i=0;i<list.size();i++){
        y_den=0;
        std::cout<<"\norigin: "<<i<<"\t";
        for(std::vector<int>::iterator it = list.at(i).begin(); it != list.at(i).end(); ++it){
  //        std::cout<<*it<<" "<<M_num[k][*it+2]<<"\t";
          y_den+=M_den[k][*it+2];
        }
        error=(double) abs(1./y_den-M_num_der[k][i+1]/(y_den*y_den));
        std::cout<<y_den<<"\t("<<(float) M_num_der[k][i+1]/y_den<<"   \t+- "<<error<<")";
        M_den_der[k][i+1]=y_den;
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

    std::cout<<"\n";

    TCanvas c("c", "canvas", 1300, 900);
    c.SetGrid();
    //gPad->SetLogy();

    string origin[6] = {"PU","FAKE","FAKE_b/c","GEANT","FRAG","B/C"};
    int colors[6] = {2,30,38,44,12,4};

    auto leg = new TLegend(0.2,0.2,0.35,0.4);//x1,y1,x2,y2
    TH1D** py = new TH1D*[n_Xbins];
    double py_bin=0;
    for(int i=1;i<=6;i++){
      py[i] = new TH1D(Form("syj%d",i),"",Nbins,0,pt_max);
      for(int k=0;k<Nbins;k++){
        py_bin=(double) M_num_der[k][i]/M_den_der[k][i];
        py[i]->AddBinContent(k+1,py_bin);
        py[i]->SetStats(0);
        py[i]->GetYaxis()->SetRangeUser(1e-3, 1.);
        py[i]->GetXaxis()->SetTitle("jet pT [GeV]");
        py[i]->GetYaxis()->SetTitle("track acceptance");
        py[i]->SetLineWidth(2);
        py[i]->SetLineColor(colors[i-1]);
        py[i]->SetOption("col");
        py[i]->SetMarkerStyle(5);
        py[i]->SetMarkerSize(2);
      }
      leg->AddEntry(py[i],origin[i-1].c_str(),"l");
        py[i]->Draw("same hist");
        py[i]->Draw("hist p same");
    }
      leg->Draw();
      c.SaveAs(("/home/salomon/Private/atlas/FTPF/Selector/plots/origin/eff_"+alg+"_jetpT.pdf").c_str());

    }
    std::cout<<"\n\n";
}
