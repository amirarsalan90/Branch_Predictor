#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <map>
#include <cmath>
#include <iomanip>
#include "tools.h"

using namespace std;

/*
string filename = "gcc_trace.txt";
string method = "hybrid";

int k = 8;
int m1 = 14;
int n = 10;
int m2 = 5;
*/

int main(int argc, char *argv[]){
    /*
    char *p1arg, *p2arg, *p3arg, *p4arg, *p5arg, *p6arg, *p7arg, *p8arg;
    int BLOCK_SIZE, CACHE1_SIZE, CACHE1_ASSOC, CACHE2_SIZE, CACHE2_ASSOC, REP_POL, INC_PROP;
    long ret1 = strtol(argv[1], &p1arg, 10);

    BLOCK_SIZE = ret1;

    char *testvar = argv[8];
    */
    ////////////////////////////////

    char *p2arg, *p3arg, *p4arg, *p5arg;
    int ret2, ret3, ret4, ret5;
    int m,n,m1,m2,k;
    string filename;
    string method = argv[1];

    if (method == "smith") {
        method = "smith";
        ret2 = strtol(argv[2], &p2arg, 10);
        n = ret2;
        filename = argv[3];
    }

    if (method == "bimodal"){
        method = "bimodal";
        ret2 = strtol(argv[2], &p2arg, 10);
        m = ret2;
        filename = argv[3];
    }

    if (method == "gshare"){
        method = "gshare";
        ret2 = strtol(argv[2], &p2arg, 10);
        ret3 = strtol(argv[3], &p3arg, 10);
        m = ret2;
        n = ret3;
        filename = argv[4];
    }

    if (method == "hybrid"){
        method = "hybrid";
        ret2 = strtol(argv[2], &p2arg, 10);
        ret3 = strtol(argv[3], &p3arg, 10);
        ret4 = strtol(argv[4], &p4arg, 10);
        ret5 = strtol(argv[5], &p5arg, 10);
        k = ret2;
        m1 = ret3;
        n = ret4;
        m2 = ret5;
        filename = argv[6];
    }




/////////////////////////////////////////////smith
    if (method == "smith"){
        nsmith predictor(n);
        int line_counter = 0;
        ifstream file (filename.c_str());
        string line;
        while (getline(file, line)){

            //predictor.insert_data(line.substr(0,6), line[7]);
            predictor.predict(line[7]);
            line_counter += 1;
        }

        cout << "COMMAND" <<"\n";
        cout << "./sim " << method << " " << n << " " << filename << "\n";
        cout << "OUTPUT" << "\n";
        cout << "number of predictions:" << "\t" << line_counter << "\n";
        int num_mispredictions = predictor.return_mispredictions();
        cout << "number of mispredictions:" << "\t" << num_mispredictions << "\n";
        double misprediction_rate = ((double)num_mispredictions / (double)line_counter);
        cout << fixed << showpoint << setprecision(2);
        cout << "misprediction rate:" << "\t" << misprediction_rate*100 << "%" << "\n";
        int final_counter = predictor.return_counter();
        cout << "FINAL COUNTER CONTENT:" << "\t" << final_counter;
    }







    ////////////////////////////////////////bimodal
    if (method == "bimodal"){
        int misprediction = 0;

        int num_rows = pow(2,m);
        int bimodal_matrix[num_rows];

        int j=0;
        for (j=0; j<num_rows; j++){
            bimodal_matrix[j] = 4;
        }

        int line_counter = 0;

        ifstream file (filename.c_str());
        string line;

        while (getline(file, line)){

            string thebinary = hexstring_to_binstring(line.substr(0,6));
            //cout << thebinary << "\n";
            string final_binary;// = thebinary.substr(thebinary.length()-m-2, m);

            final_binary = thebinary.substr(thebinary.length()-m-2, m);


            int index_number = return_decimal_from_binary(final_binary);

            char actual = line[7];

            if (bimodal_matrix[index_number] != 0 && bimodal_matrix[index_number] != 7){
                if (actual == 't'){
                    if (bimodal_matrix[index_number] >= 4){
                        bimodal_matrix[index_number] += 1;
                    } else if (bimodal_matrix[index_number] < 4){
                        misprediction += 1;
                        bimodal_matrix[index_number] += 1;
                    }
                } else if (actual == 'n'){
                    if (bimodal_matrix[index_number] >= 4){
                        misprediction += 1;
                        bimodal_matrix[index_number] -= 1;
                    } else if (bimodal_matrix[index_number] < 4){
                        bimodal_matrix[index_number] -= 1;
                    }
                }
            } else if (bimodal_matrix[index_number] == 0) {
                if (actual == 't'){
                    misprediction += 1;
                    bimodal_matrix[index_number] += 1;
                }
            } else if (bimodal_matrix[index_number] == 7){
                if (actual == 't'){

                }else if (actual == 'n'){
                    misprediction += 1;
                    bimodal_matrix[index_number] -= 1;
                }
            }

            line_counter += 1;

        }

        cout << "COMMAND" <<"\n";
        cout << "./sim " << method << " " << m << " " << filename << "\n";
        cout << "OUTPUT" << "\n";
        cout << "number of predictions:" << "\t" << line_counter << "\n";
        cout << "number of mispredictions:" << "\t" << misprediction << "\n";
        double misprediction_rate = ((double)misprediction / (double)line_counter);
        cout << fixed << showpoint << setprecision(2);
        cout << "misprediction rate:" << "\t" << misprediction_rate*100 << "%" << "\n";
        cout << "FINAL BIMODAL CONTENTS" << "\n";
        int final_bi_counter;
        for (final_bi_counter=0;final_bi_counter<num_rows;final_bi_counter++){
            cout << final_bi_counter << "\t" << bimodal_matrix[final_bi_counter] << "\n";
        }
    }


    /////////////////////////////////////GShare
    if (method == "gshare"){
        int misprediction = 0;

        int num_rows = pow(2,m);
        int gshare_matrix[num_rows];

        int j=0;
        for (j=0; j<num_rows; j++){
            gshare_matrix[j] = 4;
        }

        string GHR(n, '0');
        //cout << GHR << "\n";

        ifstream file (filename.c_str());
        string line;

        int line_counter = 0;

        while (getline(file, line)){
            string thebinary = hexstring_to_binstring(line.substr(0,6));

            string m_binary = thebinary.substr(thebinary.length()-m-2, m);
            string n_binary = m_binary.substr(m_binary.length()-n, n);
            string n_binary_xored = calc_xor(n_binary, GHR, n);

            string index_binary = "";

            //int k = 0;
            //int z = 0;
            for (int k=0;k<m-n;k++){
                index_binary += m_binary[k];
            }
            for (int z=0; z<n; z++){
                index_binary += n_binary_xored[z];
            }

            int index_number = return_decimal_from_binary(index_binary);


            char actual = line[7];

            if (gshare_matrix[index_number] != 0 && gshare_matrix[index_number] != 7){
                if (actual == 't'){
                    if (gshare_matrix[index_number] >= 4){
                        gshare_matrix[index_number] += 1;
                    } else if (gshare_matrix[index_number] < 4){
                        misprediction += 1;
                        gshare_matrix[index_number] += 1;
                    }
                } else if (actual == 'n'){
                    if (gshare_matrix[index_number] >= 4){
                        misprediction += 1;
                        gshare_matrix[index_number] -= 1;
                    } else if (gshare_matrix[index_number] < 4){
                        gshare_matrix[index_number] -= 1;
                    }
                }
            } else if (gshare_matrix[index_number] == 0) {
                if (actual == 't'){
                    misprediction += 1;
                    gshare_matrix[index_number] += 1;
                }
            } else if (gshare_matrix[index_number] == 7){
                if (actual == 't'){

                }else if (actual == 'n'){
                    misprediction += 1;
                    gshare_matrix[index_number] -= 1;
                }
            }



            if (actual == 't'){
                string GHR_temp(n,'0');
                for (int p=1;p<n;p++){
                    GHR_temp[p] = GHR[p-1];
                }
                GHR_temp[0] = '1';
                GHR = GHR_temp;
            }else if (actual == 'n'){
                string GHR_temp(n,'0');
                for (int p=1;p<n;p++){
                    GHR_temp[p] = GHR[p-1];
                }
                GHR_temp[0] = '0';
                GHR = GHR_temp;
            }


            line_counter += 1;

        }

        cout << "COMMAND" <<"\n";
        cout << "./sim " << method << " " << m << " " << n << " " << filename << "\n";
        cout << "OUTPUT" << "\n";
        cout << "number of predictions:" << "\t" << line_counter << "\n";
        cout << "number of mispredictions:" << "\t" << misprediction << "\n";
        double misprediction_rate = ((double)misprediction / (double)line_counter);
        cout << fixed << showpoint << setprecision(2);
        cout << "misprediction rate:" << "\t" << misprediction_rate*100 << "%" << "\n";
        cout << "FINAL GSHARE CONTENTS" << "\n";
        int final_g_counter;
        for (final_g_counter=0;final_g_counter<num_rows;final_g_counter++){
            cout << final_g_counter << "\t" << gshare_matrix[final_g_counter] << "\n";
        }
    }


    /////////////////////////////////////Hybrid
    if (method == "hybrid"){
        int misprediction_total = 0;
        int misprediction_gshare = 0;
        int misprediction_bimodal = 0;

        int num_rows_bimodal = pow(2,m2);
        int bimodal_matrix[num_rows_bimodal];

        int num_rows_gshare = pow(2, m1);
        int gshare_matrix[num_rows_gshare];

        int num_rows_hybrid = pow(2, k);
        int hybrid_matrix[num_rows_hybrid];


        int j;
        for (j=0; j<num_rows_bimodal; j++){
            bimodal_matrix[j] = 4;
        }
        for (j=0;j<num_rows_gshare; j++){
            gshare_matrix[j] = 4;
        }
        for (j=0;j<num_rows_hybrid; j++){
            hybrid_matrix[j] = 1;
        }

        string GHR(n, '0');

        ifstream file (filename.c_str());
        string line;

        int line_counter = 0;
        int bimodal_was_true;
        int gshare_was_true;

        int the_gshare_prediction;
        int the_bimodal_prediction;

        while (getline(file, line)){
            int bimodal_is_zero = 0;
            int bimodal_is_seven = 0;
            int gshare_is_zero = 0;
            int gshare_is_seven = 0;

            gshare_was_true = 0;
            bimodal_was_true = 0;

            string thebinary = hexstring_to_binstring(line.substr(0,6));
            string final_binary;
            final_binary = thebinary.substr(thebinary.length()-m2-2, m2);
            int index_number_bimodal = return_decimal_from_binary(final_binary);


            string m_binary = thebinary.substr(thebinary.length()-m1-2, m1);
            string n_binary = m_binary.substr(m_binary.length()-n, n);
            string n_binary_xored = calc_xor(n_binary, GHR, n);
            string index_binary = "";
            for (int w=0;w<m1-n;w++){
                index_binary += m_binary[w];
            }
            for (int z=0; z<n; z++){
                index_binary += n_binary_xored[z];
            }
            int index_number_gshare = return_decimal_from_binary(index_binary);


            string final_binary_hybrid;
            final_binary_hybrid = thebinary.substr(thebinary.length()-k-2, k);
            int index_number_hybrid = return_decimal_from_binary(final_binary_hybrid);

            char actual = line[7];


            if (gshare_matrix[index_number_gshare] != 0 && gshare_matrix[index_number_gshare] != 7){
                if (actual == 't'){
                    if (gshare_matrix[index_number_gshare] >= 4){
                        gshare_matrix[index_number_gshare] += 1;
                        gshare_was_true = 1;
                        the_gshare_prediction = 1;
                    } else if (gshare_matrix[index_number_gshare] < 4){
                        misprediction_gshare += 1;
                        gshare_matrix[index_number_gshare] += 1;
                        gshare_was_true = 0;
                        the_gshare_prediction = 0;
                    }
                } else if (actual == 'n'){
                    if (gshare_matrix[index_number_gshare] >= 4){
                        misprediction_gshare += 1;
                        gshare_matrix[index_number_gshare] -= 1;
                        gshare_was_true = 0;
                        the_gshare_prediction = 1;
                    } else if (gshare_matrix[index_number_gshare] < 4){
                        gshare_matrix[index_number_gshare] -= 1;
                        gshare_was_true = 1;
                        the_gshare_prediction = 0;
                    }
                }
            } else if (gshare_matrix[index_number_gshare] == 0) {
                gshare_is_zero = 1;
                the_gshare_prediction = 0;
                if (actual == 't'){
                    misprediction_gshare += 1;
                    gshare_matrix[index_number_gshare] += 1;
                    gshare_was_true = 0;
                } else if (actual == 'n'){
                    gshare_was_true = 1;
                }
            } else if (gshare_matrix[index_number_gshare] == 7){
                gshare_is_seven = 1;
                the_gshare_prediction = 1;
                if (actual == 't'){
                    gshare_was_true = 1;
                }else if (actual == 'n'){
                    misprediction_gshare += 1;
                    gshare_matrix[index_number_gshare] -= 1;
                    gshare_was_true = 0;
                }
            }




            if (bimodal_matrix[index_number_bimodal] != 0 && bimodal_matrix[index_number_bimodal] != 7){
                if (actual == 't'){
                    if (bimodal_matrix[index_number_bimodal] >= 4){
                        bimodal_matrix[index_number_bimodal] += 1;
                        bimodal_was_true = 1;
                        the_bimodal_prediction = 1;
                    } else if (bimodal_matrix[index_number_bimodal] < 4){
                        misprediction_bimodal += 1;
                        bimodal_matrix[index_number_bimodal] += 1;
                        bimodal_was_true = 0;
                        the_bimodal_prediction = 0;
                    }
                } else if (actual == 'n'){
                    if (bimodal_matrix[index_number_bimodal] >= 4){
                        misprediction_bimodal += 1;
                        bimodal_matrix[index_number_bimodal] -= 1;
                        bimodal_was_true = 0;
                        the_bimodal_prediction = 1;
                    } else if (bimodal_matrix[index_number_bimodal] < 4){
                        bimodal_matrix[index_number_bimodal] -= 1;
                        bimodal_was_true = 1;
                        the_bimodal_prediction = 0;
                    }
                }
            } else if (bimodal_matrix[index_number_bimodal] == 0) {
                bimodal_is_zero = 1;
                the_bimodal_prediction = 0;
                if (actual == 't'){
                    misprediction_bimodal += 1;
                    bimodal_matrix[index_number_bimodal] += 1;
                    bimodal_was_true = 0;
                } else if (actual == 'n'){
                    bimodal_was_true = 1;
                }
            } else if (bimodal_matrix[index_number_bimodal] == 7){
                bimodal_is_seven = 1;
                the_bimodal_prediction = 1;
                if (actual == 't'){
                    bimodal_was_true = 1;
                }else if (actual == 'n'){
                    misprediction_bimodal += 1;
                    bimodal_matrix[index_number_bimodal] -= 1;
                    bimodal_was_true = 0;
                }
            }


            //// reversing the matrix that wasn't used
            if (hybrid_matrix[index_number_hybrid] >= 2){
                if (gshare_was_true == 0){
                    misprediction_total += 1;
                }
                if (bimodal_matrix[index_number_bimodal] != 0 && bimodal_matrix[index_number_bimodal] != 7){
                    if (actual == 't'){
                        if (bimodal_matrix[index_number_bimodal] >= 4){
                            bimodal_matrix[index_number_bimodal] -= 1;
                        } else if (bimodal_matrix[index_number_bimodal] < 4){
                            misprediction_bimodal -= 1;
                            bimodal_matrix[index_number_bimodal] -= 1;
                        }
                    } else if (actual == 'n'){
                        if (bimodal_matrix[index_number_bimodal] >= 4){
                            misprediction_bimodal -= 1;
                            bimodal_matrix[index_number_bimodal] += 1;
                        } else if (bimodal_matrix[index_number_bimodal] < 4){
                            bimodal_matrix[index_number_bimodal] += 1;
                        }
                    }
                } else if (bimodal_matrix[index_number_bimodal] == 0) {
                    if (actual == 't'){
                        misprediction_bimodal -= 1;
                        bimodal_matrix[index_number_bimodal] -= 1;
                    } else if (actual == 'n'){
                        if (bimodal_is_zero == 0){
                            bimodal_matrix[index_number_bimodal] += 1;
                        }
                    }
                } else if (bimodal_matrix[index_number_bimodal] == 7){
                    if (actual == 't'){
                        if (bimodal_is_seven == 0){
                            bimodal_matrix[index_number_bimodal] -= 1;
                        }
                    }else if (actual == 'n'){
                        misprediction_bimodal -= 1;
                        bimodal_matrix[index_number_bimodal] += 1;
                    }
                }
            }else if (hybrid_matrix[index_number_hybrid] < 2){
                if (bimodal_was_true == 0){
                    misprediction_total += 1;
                }
                if (gshare_matrix[index_number_gshare] != 0 && gshare_matrix[index_number_gshare] != 7){
                    if (actual == 't'){
                        if (gshare_matrix[index_number_gshare] >= 4){
                            gshare_matrix[index_number_gshare] -= 1;
                        } else if (gshare_matrix[index_number_gshare] < 4){
                            misprediction_gshare -= 1;
                            gshare_matrix[index_number_gshare] -= 1;
                        }
                    } else if (actual == 'n'){
                        if (gshare_matrix[index_number_gshare] >= 4){
                            misprediction_gshare -= 1;
                            gshare_matrix[index_number_gshare] += 1;
                        } else if (gshare_matrix[index_number_gshare] < 4){
                            gshare_matrix[index_number_gshare] += 1;
                        }
                    }
                } else if (gshare_matrix[index_number_gshare] == 0) {
                    if (actual == 't'){
                        misprediction_gshare -= 1;
                        gshare_matrix[index_number_gshare] -= 1;
                    } else if (actual == 'n'){
                        if (gshare_is_zero == 0){
                            gshare_matrix[index_number_gshare] += 1;
                        }
                    }
                } else if (gshare_matrix[index_number_gshare] == 7){
                    if (actual == 't'){
                        if (gshare_is_seven == 0){
                            gshare_matrix[index_number_gshare] -= 1;
                        }
                    }else if (actual == 'n'){
                        misprediction_gshare -= 1;
                        gshare_matrix[index_number_gshare] += 1;
                    }
                }
            }

            ////updating the global history regardless of hybrid matrix for gshare matrix
            //cout << GHR << "\n";
            if (actual == 't'){
                string GHR_temp(n,'0');
                for (int p=1;p<n;p++){
                    GHR_temp[p] = GHR[p-1];
                }
                GHR_temp[0] = '1';
                GHR = GHR_temp;
            }else if (actual == 'n'){
                string GHR_temp(n,'0');
                for (int p=1;p<n;p++){
                    GHR_temp[p] = GHR[p-1];
                }
                GHR_temp[0] = '0';
                GHR = GHR_temp;
            }

            if (gshare_was_true == 1 && bimodal_was_true == 0){
                if (hybrid_matrix[index_number_hybrid] < 3){
                    hybrid_matrix[index_number_hybrid] += 1;
                }
            } else if(gshare_was_true == 0 && bimodal_was_true == 1){
                if (hybrid_matrix[index_number_hybrid] > 0){
                    hybrid_matrix[index_number_hybrid] -= 1;
                }
            }

            line_counter += 1;

        }


        cout << "COMMAND" <<"\n";
        cout << "./sim " << method << " " << k << " " << m1 << " " << n << " " << m2 << " " << filename << "\n";
        cout << "OUTPUT" << "\n";
        cout << "number of predictions:" << "\t" << line_counter << "\n";
        cout << "number of mispredictions:" << "\t" << misprediction_total << "\n";
        double misprediction_rate = ((double)misprediction_total / (double)line_counter);
        cout << fixed << showpoint << setprecision(2);
        cout << "misprediction rate:" << "\t" << misprediction_rate*100 << "%" << "\n";
        cout << "FINAL CHOOSER CONTENTS" << "\n";
        int final_c_counter;
        for (final_c_counter=0;final_c_counter<num_rows_hybrid;final_c_counter++){
            cout << final_c_counter << "\t" << hybrid_matrix[final_c_counter] << "\n";

        }
        cout << "FINAL GSHARE CONTENTS" << "\n";
        for (final_c_counter=0;final_c_counter<num_rows_gshare;final_c_counter++){
            cout << final_c_counter << "\t" << gshare_matrix[final_c_counter] << "\n";

        }
        cout << "FINAL BIMODAL CONTENTS" << "\n";
        for (final_c_counter=0;final_c_counter<num_rows_bimodal;final_c_counter++){
            cout << final_c_counter << "\t" << bimodal_matrix[final_c_counter] << "\n";
        }
        //cout << misprediction_total;
    }

    return 0;
}
