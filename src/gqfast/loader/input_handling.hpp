#ifndef input_handling_
#define input_handling_

#include <dlfcn.h>             // dll functions
#include <utility>             // std::pair
#include "global_vars.hpp"

template <typename T>
class sort_comparator
{
public:
    inline bool operator() (const pair<T, int> & a, const pair<T, int> & b)
    {
        return a.second > b.second;
    }
};

class sort_comparator2
{
public:
    inline bool operator() (const pair<int, double> & a, const pair<int, double> & b)
    {
        return a.second > b.second;
    }
};

template <typename T>
pair<T, int> * top_k(T* result, int k, int domain) {
  
    vector<pair<T,int> > pairs;
    pairs.resize(domain);

    for (int i=0; i < domain; i++) {
        if (result[i] > 0) {
            pairs[i].first = i;
            pairs[i].second = result[i];
        }            
    }
    
    sort(pairs.begin(), pairs.end(), sort_comparator<T>());

    pair<T, int> * result_pairs = new pair<T,int>[k];
    for (int i=0; i<k; i++) {
        result_pairs[i].first = 0;
        result_pairs[i].second = 0;
    }

    for (int i = 0; i < k;  i++) {

        result_pairs[i].first = pairs[i].first;
        result_pairs[i].second = pairs[i].second;
    }
    
    return result_pairs; 
}

pair<int, double> * top_k(double* result, int k, int domain) {
  
    vector<pair<int,double> > pairs;
    pairs.resize(domain);

    for (int i=0; i < domain; i++) {
        if (result[i] > 0) {
            pairs[i].first = i;
            pairs[i].second = result[i];
        }            
    }
    
    sort(pairs.begin(), pairs.end(), sort_comparator2());

    pair<int, double> * result_pairs = new pair<int,double>[k];
    for (int i=0; i<k; i++) {
        result_pairs[i].first = 0;
        result_pairs[i].second = 0;
    }

    for (int i = 0; i < k;  i++) {

        result_pairs[i].first = pairs[i].first;
        result_pairs[i].second = pairs[i].second;
    }
    
    return result_pairs; 
}

void handle_input(string func_name, int r_pos, char result_data_type) {
    
    // cerr << "a1\n";
    int domain_temp = metadata.idx_domains[r_pos][0];
    string filename = "./test_cases/" + func_name + ".so";
    // cerr << "metadata idx_max_frag_sizes[0]" << metadata.idx_max_fragment_sizes[0] << "\n";
    int* cold_checks;
    int* null_checks;
    int count = 0;
    // cerr << "a2\n";
    if (result_data_type == 'd') {
    // load the symbol
        cout << "Opening " << filename << "\n";
        
        void* handle = dlopen(filename.c_str(), RTLD_NOW);
        if (!handle) {
            // cerr << "Cannot open library: " << dlerror() << '\n';
            return;
        }

        cout << "Loading symbol query_type...\n";
        typedef double* (*query_type)(int **);

    // reset errors
        dlerror();
        query_type query = (query_type) dlsym(handle, func_name.c_str());
        const char *dlsym_error = dlerror();
        if (dlsym_error) {
            // cerr << "Cannot load symbol 'query_type': " << dlsym_error <<
            '\n';
            dlclose(handle);
            return;
        }

        double* cold_result = query(&cold_checks);
        double* result = query(&null_checks);

        for (int i=0; i<domain_temp; i++) {        
            if (null_checks[i]){
                count++;
                if (count == 1) {
                    benchmark_t2 = chrono::steady_clock::now();
                }
            }
        }

    // close the library
        cout << "Closing library...\n";
        dlclose(handle);

        chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(benchmark_t2 - benchmark_t1);
        cout << "Query " << filename << " processed in " << time_span.count() << " seconds.\n\n";
        

        pair<int, double> * tops_result = top_k(result, 20, domain_temp);

        for (int i=0; i<20; i++) {
            cout << "Position " << tops_result[i].first << ": " << tops_result[i].second << "\n";
        }

        delete[] result;
    
        delete[] cold_result;
    
    }
    else if (result_data_type == 'i') {
        cout << "Opening " << filename << "\n";
    
        void* handle = dlopen(filename.c_str(), RTLD_NOW);
        if (!handle) {
            cerr << "Cannot open library: " << dlerror() << '\n';
            return;
        }

        cout << "Loading symbol query_type...\n";
        typedef int* (*query_type)(int **);

    // reset errors
        dlerror();
        query_type query = (query_type) dlsym(handle, func_name.c_str());
        const char *dlsym_error = dlerror();
        if (dlsym_error) {
            cerr << "Cannot load symbol 'query_type': " << dlsym_error <<
            '\n';
            dlclose(handle);
            return;
        }

        int* cold_result = query(&cold_checks);
        int* result = query(&null_checks);

        for (int i=0; i<domain_temp; i++) {        
            if (null_checks[i]){
                count++;
                if (count == 1) {
                   benchmark_t2 = chrono::steady_clock::now();
                }
            }
        }

    // close the library
        cout << "Closing library...\n";
        dlclose(handle);

        chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(benchmark_t2 - benchmark_t1);
        cout << "Query " << filename << " processed in " << time_span.count() << " seconds.\n\n";
        

        pair<int, int> * tops_result = top_k(result, 20, domain_temp);

        for (int i=0; i<20; i++) {
            cout << "Position " << tops_result[i].first << ": " << tops_result[i].second << "\n";
        }

        delete[] result;
    
        delete[] cold_result;



    }


    delete[] cold_checks;
    delete[] null_checks;
}




#endif