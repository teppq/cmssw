#include "DataFormats/HcalDigi/interface/HcalUpgradeQIESample.h"

static const float nominal_adc2fc[256] = {-1.5f, 1.5f, 4.5f, 7.5f, 10.5f, 13.5f, 16.5f, 19.5f, 22.5f, 25.5f, 28.5f, 31.5f, 34.5f, 37.5f, 40.5f, 43.5f,            //16 *3fC
                                          48.0f, 54.0f, 60.0f, 66.0f, 72.0f, 78.0f, 84.0f, 90.0f, 96.0f, 102.0f, 108.0f, 114.0f, 120.0f, 126.0f, 132.0f, 138.0f, 144.0f, 150.0f, 156.0f, 162.0f, // 20 * 6fC
                                          171.0f, 183.0f, 195.0f, 207.0f, 219.0f, 231.0f, 243.0f, 255.0f, 267.0f, 279.0f, 291.0f, 303.0f, 315.0f, 327.0f, 339.0f, 351.0f, 363.0f, 375.0f, 387.0f, 399.0f, 411.0f, // 21 * 12fC
                                          429.0f, 453.0f, 477.0f, 501.0f, 525.0f, 549.0f, 573.0f,  // 7 * 24 fC

					  
                                          565.0f, 589.0f, 613.0f, 637.0f, 661.0f, 685.0f, 709.0f, 733.0f, 757.0f, 781.0f, 805.0f, 829.0f, 853.0f, 877.0f, 901.0f, 925.0f,
					  961.0f, 1009.0f, 1057.0f, 1105.0f, 1153.0f, 1201.0f, 1249.0f, 1297.0f, 1345.0f, 1393.0f, 1441.0f, 1489.0f, 1537.0f, 1585.0f, 1633.0f, 1681.0f, 1729.0f, 1777.0f, 1825.0f, 1873.0f,
                                          1945.0f, 2041.0f, 2137.0f, 2233.0f, 2329.0f, 2425.0f, 2521.0f, 2617.0f, 2713.0f, 2809.0f, 2905.0f, 3001.0f, 3097.0f, 3193.0f, 3289.0f, 3385.0f, 3481.0f, 3577.0f, 3673.0f, 3769.0f, 3865.0f,
                                          4009.0f, 4201.0f, 4393.0f, 4585.0f, 4777.0f, 4969.0f, 5161.0f,


                                          5097.0f, 5289.0f, 5481.0f, 5673.0f, 5865.0f, 6057.0f, 6249.0f, 6441.0f, 6633.0f, 6825.0f, 7017.0f, 7209.0f, 7401.0f, 7593.0f, 7785.0f, 7977.0f,
                                          8265.0f, 8649.0f, 9033.0f, 9417.0f, 9801.0f, 10185.0f, 10569.0f, 10953.0f, 11337.0f, 11721.0f, 12105.0f, 12489.0f, 12873.0f, 13257.0f, 13641.0f, 14025.0f, 14409.0f, 14793.0f, 15177.0f, 15561.0f,
                                          16137.0f, 16905.0f, 17673.0f, 18441.0f, 19209.0f, 19977.0f, 20745.0f, 21513.0f, 22281.0f, 23049.0f, 23817.0f, 24585.0f, 25353.0f, 26121.0f, 26889.0f, 27657.0f, 28425.0f, 29193.0f, 29961.0f, 30729.0f, 31497.0f,
                                          32649.0f, 34185.0f, 35721.0f, 37257.0f, 38793.0f, 40329.0f, 41865.0f,


                                          41801.0f, 43337.0f, 44873.0f, 46409.0f, 47945.0f, 49481.0f, 51017.0f, 52553.0f, 54089.0f, 55625.0f, 57161.0f, 58697.0f, 60233.0f, 61769.0f, 63305.0f, 64841.0f,
                                          67145.0f, 70217.0f, 73289.0f, 76361.0f, 79433.0f, 82505.0f, 85577.0f, 88649.0f, 91721.0f, 94793.0f, 97865.0f, 100937.0f, 104009.0f, 107081.0f, 110153.0f, 113225.0f, 116297.0f, 119369.0f, 122441.0f, 125513.0f,
                                          130121.0f, 136265.0f, 142409.0f, 148553.0f, 154697.0f, 160841.0f, 166985.0f, 173129.0f, 179273.0f, 185417.0f, 191561.0f, 197705.0f, 203849.0f, 209993.0f, 216137.0f, 222281.0f, 228425.0f, 234569.0f, 240713.0f, 246857.0f, 253001.0f, 
                                          262217.0f, 274505.0f, 286793.0f, 299081.0f, 311369.0f, 323657.0f, 335945.0f};

HcalUpgradeQIESample::HcalUpgradeQIESample(int adc, int capid, int fiber, int fiberchan, bool dv, bool er) {
  theSample=(adc&0xff) | ((capid&0x3)<<8) |
    (((fiber-1)&0x7)<<14) | ((fiberchan&0x3)<<12) |
    ((dv)?(0x0400):(0)) | ((er)?(0x0800):(0));
}

double HcalUpgradeQIESample::nominal_fC() const {
  return nominal_adc2fc[adc()];
}

std::ostream& operator<<(std::ostream& s, const HcalUpgradeQIESample& samp) {
  s << "ADC=" << samp.adc() << ", capid=" << samp.capid();
  if (samp.er()) s << ", ER";
  if (samp.dv()) s << ", DV";
  return s;
}
