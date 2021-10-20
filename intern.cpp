#include <bits/stdc++.h>

//I WISH U LUCK
using namespace std;

pair<string, int> count_paramters_and_save_text()
{

    ifstream text_file;
    text_file.open("sample.txt");

    string cur_str, all_text;
    int amount_of_mandatory_paramterers = 0, len_cur_str = 0;

    while (getline(text_file, cur_str))
    {
        
        all_text += cur_str + '\n';
        len_cur_str = size(cur_str);

        for (int i = 0; i < len_cur_str; i++)
        {
            if (cur_str[i] == '*' && i - 1 >= 0 && cur_str[i - 1] == '{')
            {
                amount_of_mandatory_paramterers++;
            }
        }

    }

    text_file.close();

    return {all_text, amount_of_mandatory_paramterers};
}

vector<string> take_parameters()
{

    ifstream parameters_file;
    parameters_file.open("parameter.txt");

    vector<string> parameters;
    string cur_parameter;

    while (getline(parameters_file, cur_parameter))
    {
        parameters.push_back(cur_parameter);
    }

    parameters_file.close();

    return parameters;
}

int find_right_ind(int left_ind, string text)
{
    while (text[left_ind++] != '}');
    return left_ind;
}

void get_finish_sample_with_parameters(int amount_of_free_parameters, string all_text, vector<string> parameters)
{

    int left_ind, right_ind, text_len = size(all_text), cur_parameter = 0;
    for (int i = 0; i < text_len; i++)
    {
        if (all_text[i] == '{')
        {
            left_ind = i;
            right_ind = find_right_ind(left_ind, all_text);
            if (all_text[i + 1] == '*')
            {
                all_text.replace(all_text.begin() + left_ind, all_text.begin() + right_ind, parameters[cur_parameter]);
                cur_parameter++;
            }
            else
            {
                if (amount_of_free_parameters)
                {
                    all_text.replace(all_text.begin() + left_ind, all_text.begin() + right_ind, parameters[cur_parameter]);
                    amount_of_free_parameters--;
                    cur_parameter++;
                }
                else
                {
                    all_text.replace(all_text.begin() + left_ind, all_text.begin() + right_ind, "");
                }
            }
            i = right_ind;
        }
    }

    ofstream finish_file;
    finish_file.open("result.txt");
    finish_file << all_text;
    finish_file.close();
}

void solve()
{
    //обработка данных с первого файла
    pair<string, int> data = count_paramters_and_save_text();
    string text = data.first;                         // текст шаблона
    int amount_of_mandatory_parameters = data.second; // количество обязательных параметров

    //обработка данных со второго файла
    vector<string> given_parameters = take_parameters();     // параметры, которые нужно вставить
    int amount_of_given_parameters = size(given_parameters); // количество параметров, которые нужно вставить

    //cout << amount_of_given_parameters << endl;

    int amount_of_free_parameters = amount_of_given_parameters - amount_of_mandatory_parameters; // количество параметров, которые можно потратить на необязательные параметры.

    //cout << data.first << endl << data.second << endl;

    /*cout << amount_of_free_parameters << endl;
    for(auto parameter : given_parameters){
        cout << parameter << endl;
    }*/

    get_finish_sample_with_parameters(amount_of_free_parameters, text, given_parameters);
}

int main()
{
    solve();
    return 0;
}