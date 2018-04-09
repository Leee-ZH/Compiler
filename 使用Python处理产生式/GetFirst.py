# -*- coding:utf-8

import xlrd


def findprod(findx, findp):
    for ifindp in findp:
        if ifindp[0] == findx:
            return ifindp


def findfirst(findy, first):
    for ifindy in first:
        if ifindy[0] == findy:
            return ifindy[1:]


if __name__ == "__main__":
    rawbook = (xlrd.open_workbook("/Users/wave/Downloads/Course/Compiler_Principle/Compiler/Grammar.xlsx"))
    grammar = rawbook.sheet_by_index(0)
    ProductionList = list()
    for irow in range(grammar.nrows):
        rows = grammar.row_values(irow)
        if rows[0] != '':
            ProductionList.append(list())
            ProductionList[len(ProductionList)-1].append(rows[0])
            ProductionList[len(ProductionList)-1].append("")
        else:
            for prow in rows[1].split(" ")[1:]:
                if prow[0] == '\'':
                    ProductionList[len(ProductionList)-1].append(prow[1: -1])
                else:
                    ProductionList[len(ProductionList)-1].append(prow)
            ProductionList[len(ProductionList)-1].append("")
    for iProductionList in range(0, len(ProductionList)-1):
        ProductionList[iProductionList] = ProductionList[iProductionList][:-3]
    P = []
    for iProductionList in range(0, len(ProductionList)-1):
        P.append([])
        tmpProd = list()
        P[iProductionList].append(ProductionList[iProductionList][0])
        for iPL in range(0, len(ProductionList[iProductionList])):
            if ProductionList[iProductionList][iPL] == '':
                P[iProductionList].append(tmpProd)
                tmpProd = list()
            else:
                tmpProd.append(ProductionList[iProductionList][iPL])

    VT = rawbook.sheet_by_index(2)
    V = set()
    T = set()
    for irows in VT.row_values(0):
        if irows != '':
            V.add(irows)
    for irows in VT.row_values(1):
        T.add(irows)
    print(V)
    print(T)
    print()
    print("Length of V:\t" + str(len(V)))
    print("Length of T:\t" + str(len(T)))

    First = list()
    for iV in V:
        First.append([iV])
    for iT in T:
        First.append([iT])
    # print(First)
    for FirstX in First:
        if First[0][0] in T:
            FirstX.append(First[0])
        else:
            for lenPL in range(0, len(ProductionList)-1):
                if ProductionList[lenPL][0] == FirstX[0]:
                    for lenProd in range(1, len(ProductionList[lenPL])-1):
                        if ProductionList[lenPL][lenProd] in T and not ProductionList[lenPL][lenProd] in FirstX:
                            FirstX.append(ProductionList[lenPL][lenProd])

    FirstLen0 = list()
    FirstLen1 = list()
    for iFirst in First:
        FirstLen0.append(len(iFirst))
    print()

    while True:
        FirstLen1 = FirstLen0
        # 对First集中的每一个
        for iFirst in First:
            # 如果X属于V
            if iFirst[0] in V:
                # 获得X产生式
                ProdX = findprod(iFirst[0], P)
                if ProdX is None:
                    continue
                for iProdX in range(1, len(ProdX)-1):
                    tmpY = ProdX[iProdX][0]
                    if tmpY in V:
                        firstY = findfirst(tmpY, First)
                        for iFirstY in firstY:
                            if iFirstY not in iFirst:
                                iFirst.append(iFirstY)
                    elif tmpY in T:
                        if tmpY not in iFirst[1:]:
                            iFirst.append(tmpY)
        for iFirst in range(0, len(First)-1):
            FirstLen0[iFirst] = len(First[iFirst])
        if FirstLen0 == FirstLen1:
            break

    for iP in P:
        print(iP)
    print()
    for iF in First:
        for iiF in iF:
            print(iiF, end='\t')
        print()
    '''
    for iProductionList in ProductionList:
        for iiProductionList in iProductionList:
            if iiProductionList != "":
                print(iiProductionList, end="\t")
            else:
                print("\t", end="")
        print()
    '''
