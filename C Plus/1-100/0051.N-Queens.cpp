#此问题很明显是用递归的思想解决，在增加下一行时，能够选择的位置只有几个，找出能够选择的位置即可，但是问题的难点（困扰自己之处）在于vi回退的时候
#长度比较长，一直难以解决，核心操作在于每次增加元素的时候都进行比对，若元素多余列数，就执行回退操作，说明前一步的尝试错了，需要回退

#虽说所有的递归都可以用循环解决，但是本体要用循环解决的话，必须考虑vi在迭代中不断增加的情况，难以处理

#用emplace_back代替push_back，提高性能，只要有构造函数就可以用，对于部分没有构造函数的结构体只能用push_back

#vector<bool>(n,false) 方便处理，且节省内存

void addnext(vector<vector<int>>&vvi, vector<int> &vi, int col, int max)
    {
        if (vi.size() == max)
        {
            vvi.emplace_back(vi);
            //vi.clear(); 此处不必清空，有回退操作
            return;
        }
        set<int> sint;
        for (int i = 1; i <= max; ++i)
            sint.insert(i);
        set<int> si;
        for (int j = 1; j != vi.size() + 1; ++j)
        {
            si.insert(vi[j - 1]);
            si.insert(vi[j - 1] + col - j);
            si.insert(vi[j - 1] - col + j);
        }
        for (int i = 1; i <= max; ++i)
        {
            if (si.find(i) != si.end())
                sint.erase(i);
        }
        if (sint.size() == 0)
        {
            vi.pop_back();
            return;
        }
        for (int i : sint)
        {
            while (vi.size() >= col)//保证vi的元素不会多于列数，即回退操作
                vi.pop_back();
            vi.push_back(i);
            addnext(vvi, vi, col + 1, max);
        }		
    }

    vector<vector<string>> solveNQueens(int n) {
        vector<vector<int>> vvi;
        vector<int> vi;
        addnext(vvi, vi, 1, n);

        vector<vector<string>> vvs;
        vector<string> vs;
        for (auto &vei : vvi)
        {
            vs.clear();
            for (auto &i : vei)
            {
                string s(n, '.');
                s[i - 1] = 'Q';
                vs.emplace_back(s);
            }
            vvs.emplace_back(vs);
        }

        return std::move(vvs);
    }
