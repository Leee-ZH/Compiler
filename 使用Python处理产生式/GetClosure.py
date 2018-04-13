import xlrd


def prodofx(prodofxx, prodlist):
    for iprodlist in prodlist:
        if prodofxx == iprodlist[0]:
            return iprodlist[1:]


def firstofx(firstofxx, first):
    for ifirst in first:
        if ifirst[0] == firstofxx:
            return ifirst[1:]


def dotindex(listprod):
    for ilistprod in range(len(listprod)):
        if listprod[ilistprod] == 'Dot':
            return ilistprod


def getclosure(closurei):
    fi0 = closurei
    fleni0 = len(fi0)
    while True:
        for ifi0 in fi0:
            fdotindex = dotindex(ifi0[1])
            tmpb = ifi0[1][fdotindex+1]
            if tmpb in T:
                continue
            if fdotindex == len(ifi0[1])-2:
                tmpbeta = 'Empty'
            else:
                tmpbeta = ifi0[1][fdotindex+2:]
            bprod = prodofx(tmpb, ProductionList)
            for ibprod in bprod:
                ftmpy = list(['Dot'])
                for ibprodmain in ibprod:
                    ftmpy.append(ibprodmain)
                if tmpbeta == 'Empty':
                    if ifi0[2] == '$':
                        if [tmpb, ftmpy, '$'] not in fi0:
                            fi0.append([tmpb, ftmpy, '$'])
                            continue
                    else:
                        for ifirstbetaa in firstofx(ifi0[2], FirstX):
                            if [tmpb, ftmpy, ifirstbetaa] not in fi0:
                                fi0.append([tmpb, ftmpy, ifirstbetaa])
                else:
                    notemptyfirst = firstofx(tmpbeta[0], FirstX)
                    for inotempty in notemptyfirst:
                        if [tmpb, ftmpy, inotempty] not in fi0:
                            fi0.append([tmpb, ftmpy, inotempty])
        fleni1 = len(fi0)
        if fleni1 == fleni0:
            break
        fleni0 = fleni1
    return fi0


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

    VT = rawbook.sheet_by_index(2)
    V = list()
    T = list()
    for irows in VT.row_values(0):
        if irows != '':
            V.append(irows)
    for irows in VT.row_values(1):
        T.append(irows)

    for iT in T:
        ProductionList.append([iT, [iT]])

    sheet5 = rawbook.sheet_by_index(5)
    FirstX = list()
    for isheet5 in range(sheet5.nrows):
        s5row = sheet5.row_values(isheet5)
        while s5row[-1] == '':
            s5row.pop()
        FirstX.append(s5row)
    '''
    I0 = [['translation_unit!', ['Dot', 'translation_unit'], '$']]
    lenI0 = len(I0)
    lenI1 = len(I0)
    while True:
        for iI0 in I0:
            Dotindex = dotindex(iI0[1])
            tmpB = iI0[1][Dotindex+1]
            if tmpB in T:
                continue

            if Dotindex == 0:
                tmpAlpha = 'Empty'
            else:
                tmpAlpha = iI0[1][:Dotindex]

            if Dotindex == len(iI0[1])-2:
                tmpBeta = 'Empty'
            else:
                tmpBeta = iI0[1][Dotindex+2:]
            Bprod = prodofx(tmpB, ProductionList)
            for iBprod in Bprod:
                for iBprodmain in Bprod:
                    tmpy = ['Dot']
                    for iiBprodmain in iBprodmain:
                        tmpy.append(iiBprodmain)
                    if tmpBeta == 'Empty':
                        if iI0[2] == '$':
                            if [tmpB, tmpy, '$'] not in I0:
                                I0.append([tmpB, tmpy, '$'])
                                continue
                        else:
                            for iFirstbetaa in firstofx(iI0[2], FirstX):
                                if [tmpB, tmpy, iFirstbetaa] not in I0:
                                    I0.append([tmpB, tmpy, iFirstbetaa])
                    else:
                        notEmptyFirst = firstofx(tmpBeta[0], FirstX)
                        for iNotEmpty in notEmptyFirst:
                            if [tmpB, tmpy, iNotEmpty] not in I0:
                                I0.append([tmpB, tmpy, iNotEmpty])
        lenI1 = len(I0)
        if lenI1 == lenI0:
            break
        lenI0 = lenI1
    '''

    I0 = getclosure([['translation_unit!', ['Dot', 'translation_unit'], '$']])

    for iI0 in I0:
        for iiI0 in range(len(iI0)):
            print(iI0[iiI0], end="\t")
        print()
    print()

    print(len(I0))
