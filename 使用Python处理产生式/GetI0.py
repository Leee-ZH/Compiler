import xlrd


def prodofx(prodofxx, prodlist):
    for iprodlist in prodlist:
        if prodofxx == iprodlist[0]:
            return iprodlist[1:]


if __name__ == "__main__":
    rawbook = (xlrd.open_workbook("/Users/wave/Downloads/Course/Compiler_Principle/Compiler/Grammar.xlsx"))
    grammar = rawbook.sheet_by_index(3)
    ProductionList = list()
    for irows in range(grammar.nrows):
        row = grammar.row_values(irows)
        tmp = list()
        for iProd in row:
            if len(tmp) == 0:
                tmp.append(iProd)
            else:
                if iProd == '':
                    tmp.append([])
                else:
                    tmp[-1].append(iProd)
        while len(tmp[-1]) == 0:
            tmp.pop()
        ProductionList.append(tmp)
    '''
    for iPL in ProductionList:
        print(iPL)
    '''
    VT = rawbook.sheet_by_index(2)
    V = list()
    T = list()
    for irows in VT.row_values(0):
        if irows != '':
            V.append(irows)
    for irows in VT.row_values(1):
        T.append(irows)

    I0 = [['translation_unit!', ['Dot', 'translation_unit']]]
    lenI0 = len(I0)
    lenI1 = len(I0)
    while True:
        for iI0 in I0:
            if iI0[1][0] == 'Dot' and iI0[1][1] in V:
                for iprodofx in prodofx(iI0[1][1], ProductionList):
                    tmpProd = ['Dot']
                    for iiprodofx in iprodofx:
                        tmpProd.append(iiprodofx)
                    if [iI0[1][1], tmpProd] not in I0:
                        I0.append([iI0[1][1], tmpProd])
        lenI1 = len(I0)

        if lenI1 == lenI0:
            break
        lenI0 = lenI1

    for iI0 in I0:
        for iiI0 in iI0:
            print(iiI0, end="\t")
        print()

    '''
    for iP in P:
        print(iP)
    '''
