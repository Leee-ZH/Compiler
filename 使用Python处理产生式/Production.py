import xlrd

if __name__ == "__main__":
    rawbook = (xlrd.open_workbook("/Users/wave/Downloads/Course/Compiler_Principle/Compiler/Grammar.xlsx"))
    grammar = rawbook.sheet_by_index(0)
    for irow in range(grammar.nrows):
        rows = grammar.row_values(irow)
        if rows[0] != '':
            print(rows[0])
        else:
            print("\t", end='')
            for prow in rows[1].split(" ")[1:]:
                if prow[0] == '\'':
                    print(prow[1: -1], end='\t')
                else:
                    print(prow, end='\t')
            print()
