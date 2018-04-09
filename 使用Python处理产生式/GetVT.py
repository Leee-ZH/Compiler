import xlrd

if __name__ == "__main__":
    rawbook = (xlrd.open_workbook("/Users/wave/Downloads/Course/Compiler_Principle/Compiler/Grammar.xlsx"))
    grammar = rawbook.sheet_by_index(1)
    V = set()
    T = set()
    for irow in range(grammar.nrows):
        rows = grammar.row_values(irow)
        if rows[0] == '':
            for irows in rows:
                if irows != '':
                    if 'a' <= irows[0] <= 'Z' or irows[0] < 'a' or irows > 'z':
                        T.add(irows)
                    else:
                        V.add(irows)
    for iV in V:
        print(iV, end='\t')
    print()
    for iT in T:
        print(iT, end='\t')
