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


def afterdot(idot):
    idotre = list()
    for iidot in idot:
        afterindex = dotindex(iidot[1])
        if afterindex != len(iidot[1]) - 1 and iidot[1][afterindex+1] not in idotre:
            idotre.append(iidot[1][afterindex+1])
    return idotre


def getpvtfirst(path):
    frawbook = xlrd.open_workbook(path)
    fgrammar = frawbook.sheet_by_index(0)

    fproductionlist = list()
    for firows in range(fgrammar.nrows):
        frow = fgrammar.row_values(firows)
        ftmp = list()
        for iprod in frow:
            if len(ftmp) == 0:
                ftmp.append(iprod)
            else:
                if iprod == '':
                    ftmp.append([])
                else:
                    ftmp[-1].append(iprod)
        if len(ftmp[-1]) != 0:
            fproductionlist.append(ftmp)
            continue
        while len(ftmp[-1]) == 0:
            ftmp.pop()
            if ftmp not in fproductionlist:
                fproductionlist.append(ftmp)

    fvt = set()
    fv = list()
    ft = list()
    for ifpl in fproductionlist:
        if ifpl[0] != "translation_unit\'":
            fvt.add(ifpl[0])
            for iifpl in ifpl[1:]:
                for iiifpl in iifpl:
                    fvt.add(iiifpl)
    for ifvt in fvt:
        if 'a' <= ifvt[0] <= 'z':
            if ifvt not in fv:
                fv.append(ifvt)
        else:
            if ifvt not in ft:
                ft.append(ifvt)
    ft.sort()
    fv.sort()

    for fit in ft:
        fproductionlist.append([fit, [fit]])
    ffirst = list()
    for ifv in fv:
        ffirst.append([ifv])
    for ift in ft:
        ffirst.append([ift])

    for firstx in ffirst:
        if firstx[0] in ft:
            firstx.append(firstx[0])
        else:
            for flenpl in range(len(fproductionlist)):
                if fproductionlist[flenpl][0] == firstx[0]:
                    for lenprod in range(1, len(fproductionlist[flenpl])-1):
                        if fproductionlist[flenpl][0] in ft and not fproductionlist[flenpl][0] in firstx:
                            firstx.append(fproductionlist[flenpl][0])
    
    ffirstlen0 = list()
    ffirstlen1 = list()
    for ifirst in ffirst:
        ffirstlen0.append(len(ifirst))
    for ifirst in ffirst:
        ffirstlen1.append(len(ifirst))

    while True:
        for ftmplen in range(len(ffirstlen0) - 1):
            ffirstlen1[ftmplen] = ffirstlen0[ftmplen]
        for ifirst in ffirst:
            prodx = prodofx(ifirst[0], fproductionlist)
            if prodx is not None and len(prodx) != 0:
                for iprodx in prodx:
                    if iprodx[0] in fv:
                        firsty = firstofx(iprodx[0], ffirst)
                        for ifirsty in firsty:
                            if ifirsty not in ifirst:
                                ifirst.append(ifirsty)
                    elif iprodx[0] in ft:
                        if iprodx[0] not in ifirst:
                            ifirst.append(iprodx[0])
        for ifirst in range(len(ffirst)):
            ffirstlen0[ifirst] = len(ffirst[ifirst])
        if ffirstlen0 == ffirstlen1:
            break

    return sorted(fproductionlist), sorted(fv), sorted(ft), sorted(ffirst)


def getclosure(closurei):
    fi0 = closurei
    fleni0 = len(fi0)
    while True:
        for ifi0 in fi0:
            fdotindex = dotindex(ifi0[1])
            if fdotindex == len(ifi0[1])-1:
                continue
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
    return sorted(fi0)


def goto(gotoi, gotox):
    gotoj = list()
    for igotoi in gotoi:
        gotodotindex = dotindex(igotoi[1])
        if gotodotindex == len(igotoi[1]) - 1:
            continue
        gototmpx = igotoi[1][gotodotindex+1]
        gototmpappend = []
        for iigoti in range(len(igotoi[1])):
            if iigoti == gotodotindex:
                gototmpappend.append(gototmpx)
            elif iigoti == gotodotindex+1:
                gototmpappend.append('Dot')
            else:
                gototmpappend.append(igotoi[1][iigoti])
        if gototmpx == gotox:
            gotoj.append([igotoi[0], gototmpappend, igotoi[2]])
    return getclosure(gotoj)


def getitems(items):
    itemslen0 = len(items)
    while True:
        for iitems in items:
            if len(items) == 1572:              # Know that the length of items is 1572
                return items
            print(len(items))
            for ipl0 in afterdot(iitems):
                tmpitem = goto(iitems, ipl0)
                if tmpitem not in items and len(tmpitem) != 0:
                    items.append(tmpitem)
        itemslen1 = len(items)
        if itemslen1 == itemslen0:
            break
        itemslen0 = itemslen1
    return sorted(items)


def outc(items, filepath):
    countout = 0
    outputc = open(filepath, 'w')
    for iitems in range(len(items)):
        outputc.write(str(countout)+'\n')
        for iiitems in items[iitems]:
            outputc.write(str(iiitems[0])+'\t')
            for iiiitems in iiitems[1]:
                outputc.write(str(iiiitems)+'\t')
            outputc.write(str(iiitems[2])+'\n')
        outputc.write('___\n')
        countout += 1


def readitems(readpath):
    fread = xlrd.open_workbook(readpath)
    fgrammar = fread.sheet_by_index(1)
    reitems = list()
    tmpc = list()
    for firows in range(fgrammar.nrows):
        frow = fgrammar.row_values(firows)
        while frow[-1] == '':
            frow.pop()
        if frow[0] == '___':
            reitems.append(tmpc)
            tmpc = list()
        elif not str(frow[0]).isdigit():
            tmpc.append([frow[0], frow[1:-1], frow[-1]])
    for ireitems in range(len(reitems)):
        reitems[ireitems] = reitems[ireitems][1:]
    return reitems


def getabdot(statei, getv, gett):
    rea = list()
    reb = list()
    redot = list()
    for leni in range(len(statei)):
        tmpprod = statei[leni]
        tmpdotindex = dotindex(tmpprod[1])
        if tmpdotindex == len(tmpprod[1])-1:
            redot.append(1)
            continue
        else:
            redot.append(0)
        if tmpprod[1][tmpdotindex+1] in getv and tmpprod[1][tmpdotindex+1] not in reb:
            reb.append(tmpprod[1][tmpdotindex+1])
        elif tmpprod[1][tmpdotindex+1] in gett and tmpprod[1][tmpdotindex+1] not in rea:
            rea.append(tmpprod[1][tmpdotindex+1])
    return [rea, reb, redot]


def getj(alpha, upa, prod):
    for iprod in range(len(prod)):
        if prod[iprod][0] == upa:
            return iprod, prod[iprod].index(alpha)


def gettable(ansic, prod, getv, gett):
    retable = list()
    tmpgett = list()
    for igett in gett:
        tmpgett.append(igett)
    tmpgett.append('$')
    for lenansi in range(len(ansic)):
        tmpadd = list()
        for lenvt in range(len(getv) + len(tmpgett)):
            tmpadd.append('err')
        retable.append(tmpadd)
    for getk in range(len(ansic)):
        tmpik = ansic[getk]
        tmpa, tmpb, tmpdot = getabdot(tmpik, getv, gett)
        for ia in tmpa:
            tmpstate = goto(tmpik, ia)
            if tmpstate in ansic:
                retable[getk][tmpgett.index(ia)] = 'S ' + str(ansic.index(tmpstate))
        for ib in tmpb:
            tmpstate = goto(tmpik, ib)
            if tmpstate in ansic:
                retable[getk][len(tmpgett)+getv.index(ib)] = str(ansic.index(tmpstate))
        for idot in range(len(tmpdot)):
            if tmpdot[idot] == 1:
                tmpalpha = tmpik[idot][1][:-1]
                tmpupa = tmpik[idot][0]
                tmpj = getj(tmpalpha, tmpupa, prod)
                for lengett in range(len(tmpgett)):
                    if retable[getk][lengett][0] != 'S':
                        retable[getk][lengett] = 'R ' + str(tmpj[0]) + ' ' + str(tmpj[1])
                if tmpupa == 'translation_unit!':
                    retable[getk][len(tmpgett)-1] = 'acc'
        print(getk)
    return retable


def printtable(ptable, filepath, printt, printv):
    out = open(filepath, 'w')
    out.write("\t")
    for pt in printt:
        out.write(str(pt)+"\t")
    out.write("$\t")
    for pv in printv:
        out.write(str(pv)+"\t")
    out.write("\n")
    for getk in range(len(ptable)):
        out.write(str(getk)+"\t")
        for prow in ptable[getk]:
            out.write(str(prow)+"\t")
        out.write("\n")


def printprod(prod):
    for iprod in prod:
        print(str(iprod[0]) + '\t\t', end='')
        for iiprod in iprod[1:]:
            for iiiprod in iiprod:
                print(iiiprod + '\t', end='')
            print('\t', end='')
        print()


if __name__ == "__main__":
    rawpath = "/Users/wave/Downloads/Course/Compiler_Principle/Compiler/ANSI_C.xlsx"
    # outpath0 = "/Users/wave/Downloads/Course/Compiler_Principle/Compiler/testresult.txt"
    outpath1 = "/Users/wave/Downloads/Course/Compiler_Principle/Compiler/table.txt"
    ProductionList, V, T, FirstX = getpvtfirst(rawpath)
    printprod(ProductionList)
    # I0 = getclosure([['translation_unit!', ['Dot', 'translation_unit'], '$']])
    # C = getitems([I0])
    # outc(C, outpath0)
    C = readitems(rawpath)
    Table = gettable(C, ProductionList, V, T)
    printtable(Table, outpath1, T, V)
