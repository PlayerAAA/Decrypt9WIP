#include "common.h"
#include "draw.h"
#include "fs.h"
#include "hid.h"
#include "menu.h"
#include "platform.h"
#include "i2c.h"
#include "decryptor/keys.h"
#include "decryptor/game.h"
#include "decryptor/nand.h"
#include "decryptor/nandfat.h"
#include "decryptor/titlekey.h"
#include "decryptor/selftest.h"
#include "decryptor/xorpad.h"

#define SUBMENU_START 7

MenuInfo menu[] =
{
    {
        "Opciones de GENERACION DE XORPADS", 8,
        {
            { "NCCH Padgen",                  &NcchPadgen,            0 },
            { "SD Padgen (SDinfo.bin)",       &SdPadgen,              0 },
            { "SD Padgen (SysNAND dir)",      &SdPadgenDirect,        0 },
            { "SD Padgen (EmuNAND dir)",      &SdPadgenDirect,        N_EMUNAND },
            { "CTRNAND Padgen",               &CtrNandPadgen,         0 },
            { "CTRNAND Padgen (slot0x4)",     &CtrNandPadgen,         PG_FORCESLOT4 },
            { "TWLNAND Padgen",               &TwlNandPadgen,         0 },
            { "FIRM0FIRM1 Padgen",            &Firm0Firm1Padgen,      0 }
        }
    },
    {
        "Opciones de TITLEKEY", 6,
        {
            { "Descifrar un Titlekey (archivo)",      &CryptTitlekeysFile,    0 },
            { "Descifrar Titlekey (SysNAND)",   &DumpTitlekeysNand,     0 },
            { "Descifrar Titlekey (EmuNAND)",   &DumpTitlekeysNand,     N_EMUNAND },
            { "Cifrar un Titlekey (archivo)",      &CryptTitlekeysFile,    TK_ENCRYPTED },
            { "Realizar copia de Titlekey (SysNAND)",      &DumpTitlekeysNand,     TK_ENCRYPTED },
            { "Realizar copia de Titlekey (EmuNAND)",      &DumpTitlekeysNand,     N_EMUNAND | TK_ENCRYPTED }
        }
    },
    {
        "Opciones de SYSNAND", 6,
        {
            { "Copiar/Restaurar SysNand",    NULL,                   SUBMENU_START +  0 },
            { "Realizar copia de una particion",            NULL,                   SUBMENU_START +  2 },
            { "Inyectar una particion",          NULL,                   SUBMENU_START +  4 },
            { "Realizar copia de archivo",                 NULL,                   SUBMENU_START +  6 },
            { "Inyectar archivo",               NULL,                   SUBMENU_START +  8 },
            { "Miscelaneo",             NULL,                   SUBMENU_START + 10 }
        }
    },
    {
        "Opciones de EMUNAND", 6,
        {
            { "Copiar/Restaurar EmuNand",    NULL,                   SUBMENU_START +  1 },
            { "Realizar copia de una particion",            NULL,                   SUBMENU_START +  3 },
            { "Inyectar una particion",          NULL,                   SUBMENU_START +  5 },
            { "Realizar copia de un archivo",                 NULL,                   SUBMENU_START +  7 },
            { "Inyectar un archivio",               NULL,                   SUBMENU_START +  9 },
            { "Miscelaneo",             NULL,                   SUBMENU_START + 11 }
        }
    },
    {
        "Opciones de DESCIFRADO DE CONTENIDO", 11,
        {
            { "Descifrar NCCH/NCSD",          &CryptGameFiles,        GC_NCCH_PROCESS },
            { "Cifrar NCCH/NCSD",          &CryptGameFiles,        GC_NCCH_PROCESS | GC_NCCH_ENCRYPT },
            { "Descifrar CIA (superficial)",      &CryptGameFiles,        GC_CIA_PROCESS },
            { "Descifrar CIA (completo)",         &CryptGameFiles,        GC_CIA_PROCESS | GC_CIA_DEEP },
            { "Descifrar CIA (solo CXI)",     &CryptGameFiles,        GC_CIA_PROCESS | GC_CIA_DEEP | GC_CXI_ONLY },
            { "Cifrar CIA (NCCH)",         &CryptGameFiles,        GC_CIA_PROCESS | GC_NCCH_ENCRYPT },
            { "Descifrar BOSS",               &CryptGameFiles,        GC_BOSS_PROCESS },
            { "Cifrar BOSS",               &CryptGameFiles,        GC_BOSS_PROCESS | GC_BOSS_ENCRYPT },
            { "Descifrar/Cifrar SD",       &CryptSdFiles,          0 },
            { "Descifrar SD (directorio de la SysNAND)",   &DecryptSdFilesDirect,  0 },
            { "Descifrar SD (directorio de la EmuNAND)",   &DecryptSdFilesDirect,  N_EMUNAND }
        }
    },
    {
        "Opciones de COPIA DE CARTUCHOS", 5,
        {
            { "Copiar cartucho (completo)",             &DumpGameCart,          0 },
            { "Copiar cartucho (superficial)",             &DumpGameCart,          CD_TRIM },
            { "Copiar y descifrar cartucho (completo)",   &DumpGameCart,          CD_DECRYPT },
            { "Copiar y descifrar cartucho (ligero)",   &DumpGameCart,          CD_DECRYPT | CD_TRIM },
            { "Copiar header privado (private header)",          &DumpPrivateHeader,     0 }
        }
    },
    {
        "Opciones de MANTENIMIENTO", 5,
        {
            { "Informacion del sistema",                  &SystemInfo,            0 },
            { "Crear Selftest Reference",    &SelfTest,              ST_REFERENCE },
            { "Ejecutar Selftest",                 &SelfTest,              0 },
            { "Crear Key Database",           &BuildKeyDb,            KEY_ENCRYPT },
            { "Descifrar/Cifrar Key Database",      &CryptKeyDb,            0 }
        }
    },
    // everything below is not contained in the main menu
    {
        "Opciones de copia/restauracion (SysNand)", 6, // ID 0
        {
            { "Copia de la NAND",                  &DumpNand,              0 },
            { "Copia de la NAND (menor peso)",       &DumpNand,              NB_MINSIZE },
            { "Restaurar NAND",                 &RestoreNand,           N_NANDWRITE | N_A9LHWRITE },
            { "Restaurar NAND (forzado)",        &RestoreNand,           N_NANDWRITE | N_A9LHWRITE | NR_NOCHECKS },
            { "Restaurar NAND (mantener A9LH)",     &RestoreNand,           N_NANDWRITE | NR_KEEPA9LH },
            { "Validar copia de la NAND",           &ValidateNandDump,      0 }
        }
    },
    {
        "Opciones de copia/restauracion (EmuNand)", 5, // ID 1
        {
            { "Copia de la NAND",                  &DumpNand,              N_EMUNAND },
            { "Copia de la NAND (menor peso)",       &DumpNand,              N_EMUNAND | NB_MINSIZE },
            { "Restaurar NAND",                 &RestoreNand,           N_NANDWRITE | N_EMUNAND | N_FORCEEMU },
            { "Restaurar NAND (forzado)",        &RestoreNand,           N_NANDWRITE | N_EMUNAND | N_FORCEEMU | NR_NOCHECKS },
            { "Validar copia de la NAND",           &ValidateNandDump,      0 } // same as the one in SysNAND backup & restore
        }
    },
    {
        "Opciones de copia de particion (SysNAND)", 8, // ID 2
        {
            { "Realizar copia de la particion TWLN",          &DecryptNandPartition, P_TWLN },
            { "Realizar copia de la particion TWLP",          &DecryptNandPartition, P_TWLP },
            { "Realizar copia de la particion AGBSAVE",       &DecryptNandPartition, P_AGBSAVE },
            { "Realizar copia de la particion FIRM0",         &DecryptNandPartition, P_FIRM0 },
            { "Realizar copia de la particion FIRM1",         &DecryptNandPartition, P_FIRM1 },
            { "Realizar copia de la particion CTRNAND",       &DecryptNandPartition, P_CTRNAND },
            { "Realizar copia del sector 0x96",             &DecryptSector0x96,    0 },
            { "Realizar copia del NAND Header",             &DumpNandHeader,       0 }
        }
    },
    {
        "Opciones de copia de particion (EmuNAND)", 8, // ID 3
        {
            { "Realizar copia de la particion TWLN",          &DecryptNandPartition, N_EMUNAND | P_TWLN },
            { "Realizar copia de la particion TWLP",          &DecryptNandPartition, N_EMUNAND | P_TWLP },
            { "Realizar copia de la particion AGBSAVE",       &DecryptNandPartition, N_EMUNAND | P_AGBSAVE },
            { "Realizar copia de la particion FIRM0",         &DecryptNandPartition, N_EMUNAND | P_FIRM0 },
            { "Realizar copia de la particion FIRM1",         &DecryptNandPartition, N_EMUNAND | P_FIRM1 },
            { "Realizar copia de la particion CTRNAND",       &DecryptNandPartition, N_EMUNAND | P_CTRNAND },
            { "Realizar copia del sector 0x96",             &DecryptSector0x96,    N_EMUNAND },
            { "Realizar copia del NAND Header",             &DumpNandHeader,       N_EMUNAND }
        }
    },
    {
        "Opciones inyeccion de particion (SysNAND)", 8, // ID 4
        {
            { "Inyectar copia de la particion TWLN",        &InjectNandPartition, N_NANDWRITE | P_TWLN },
            { "Inyectar copia de la particion TWLP",        &InjectNandPartition, N_NANDWRITE | P_TWLP },
            { "Inyectar copia de la particion AGBSAVE",     &InjectNandPartition, N_NANDWRITE | P_AGBSAVE },
            { "Inyectar copia de la particion FIRM0",       &InjectNandPartition, N_NANDWRITE | N_A9LHWRITE | P_FIRM0 },
            { "Inyectar copia de la particion FIRM1",       &InjectNandPartition, N_NANDWRITE | N_A9LHWRITE | P_FIRM1 },
            { "Inyectar copia de la particion CTRNAND",     &InjectNandPartition, N_NANDWRITE | P_CTRNAND },
            { "Inyectar copia del sector 0x96",           &InjectSector0x96,    N_NANDWRITE | N_A9LHWRITE },
            { "Restaurar el NAND Header ",          &RestoreNandHeader,   N_NANDWRITE | N_A9LHWRITE }
        }
    },
    {
        "Opciones inyeccion de particion (EmuNAND)", 8, // ID 5
        {
            { "Inyectar copia de la particion TWLN",        &InjectNandPartition, N_NANDWRITE | N_EMUNAND | P_TWLN },
            { "Inyectar copia de la particion TWLP",        &InjectNandPartition, N_NANDWRITE | N_EMUNAND | P_TWLP },
            { "Inyectar copia de la particion AGBSAVE",     &InjectNandPartition, N_NANDWRITE | N_EMUNAND | P_AGBSAVE },
            { "Inyectar copia de la particion FIRM0",       &InjectNandPartition, N_NANDWRITE | N_EMUNAND | P_FIRM0 },
            { "Inyectar copia de la particion FIRM1",       &InjectNandPartition, N_NANDWRITE | N_EMUNAND | P_FIRM1 },
            { "Inyectar copia de la particion CTRNAND",     &InjectNandPartition, N_NANDWRITE | N_EMUNAND | P_CTRNAND },
            { "Inyectar copia del sector 0x96",            &InjectSector0x96,    N_NANDWRITE | N_EMUNAND },
            { "Restaurar el NAND Header ",          &RestoreNandHeader,   N_NANDWRITE | N_EMUNAND }
        }
    },
    {
        "Opciones de copia de archivo (SysNAND)", 11, // ID 6
        {
            { "Realizar copia de ticket.db",               &DumpFile,             F_TICKET },
            { "Realizar copia de title.db",                &DumpFile,             F_TITLE },
            { "Realizar copia de import.db",               &DumpFile,             F_IMPORT },
            { "Realizar copia de certs.db",                &DumpFile,             F_CERTS },
            { "Realizar copia de SecureInfo_A",            &DumpFile,             F_SECUREINFO },
            { "Realizar copia de LocalFriendCodeSeed_B",   &DumpFile,             F_LOCALFRIEND },
            { "Realizar copia de movable.sed",             &DumpFile,             F_MOVABLE },
            { "Realizar copia de seedsave.bin",            &DumpFile,             F_SEEDSAVE },
            { "Realizar copia de nagsave.bin",             &DumpFile,             F_NAGSAVE },
            { "Realizar copia de nnidsave.bin",            &DumpFile,             F_NNIDSAVE },
            { "Realizar copia de friendsave.bin",          &DumpFile,             F_FRIENDSAVE }
        }
    },
    {
        "Opciones de copia de archivo (EmuNAND)", 11, // ID 7
        {
            { "Realizar copia de ticket.db",               &DumpFile,             N_EMUNAND | F_TICKET },
            { "Realizar copia de title.db",                &DumpFile,             N_EMUNAND | F_TITLE },
            { "Realizar copia de import.db",               &DumpFile,             N_EMUNAND | F_IMPORT },
            { "Realizar copia de certs.db",                &DumpFile,             N_EMUNAND | F_CERTS },
            { "Realizar copia de SecureInfo_A",            &DumpFile,             N_EMUNAND | F_SECUREINFO },
            { "Realizar copia de LocalFriendCodeSeed_B",   &DumpFile,             N_EMUNAND | F_LOCALFRIEND },
            { "Realizar copia de movable.sed",             &DumpFile,             N_EMUNAND | F_MOVABLE },
            { "Realizar copia de seedsave.bin",            &DumpFile,             N_EMUNAND | F_SEEDSAVE },
            { "Realizar copia de nagsave.bin",             &DumpFile,             N_EMUNAND | F_NAGSAVE },
            { "Realizar copia de nnidsave.bin",            &DumpFile,             N_EMUNAND | F_NNIDSAVE },
            { "Realizar copia de friendsave.bin",          &DumpFile,             N_EMUNAND | F_FRIENDSAVE }
        }
    },
    {
        "Opciones de inyeccion de archivos (SysNAND)", 11, // ID 8
        {
            { "Inyectar copia de ticket.db",             &InjectFile,           N_NANDWRITE | F_TICKET },
            { "Inyectar copia de title.db",              &InjectFile,           N_NANDWRITE | F_TITLE },
            { "Inyectar copia de import.db",             &InjectFile,           N_NANDWRITE | F_IMPORT },
            { "Inyectar copia de certs.db",              &InjectFile,           N_NANDWRITE | F_CERTS },
            { "Inyectar copia de SecureInfo_A",          &InjectFile,           N_NANDWRITE | F_SECUREINFO },
            { "Inyectar copia de LocalFriendCodeSeed_B", &InjectFile,           N_NANDWRITE | F_LOCALFRIEND },
            { "Inyectar copia de movable.sed",           &InjectFile,           N_NANDWRITE | F_MOVABLE },
            { "Inyectar copia de seedsave.bin",          &InjectFile,           N_NANDWRITE | F_SEEDSAVE },
            { "Inyectar copia de nagsave.bin",           &InjectFile,           N_NANDWRITE | F_NAGSAVE },
            { "Inyectar copia de nnidsave.bin",          &InjectFile,           N_NANDWRITE | F_NNIDSAVE },
            { "Inyectar copia de friendsave.bin",        &InjectFile,           N_NANDWRITE | F_FRIENDSAVE }
        }
    },
    {
        "Opciones de inyeccion de archivos (EmuNAND)", 11, // ID 9
        {
            { "Inyectar copia de ticket.db",             &InjectFile,           N_NANDWRITE | N_EMUNAND | F_TICKET },
            { "Inyectar copia de title.db",              &InjectFile,           N_NANDWRITE | N_EMUNAND | F_TITLE },
            { "Inyectar copia de import.db",             &InjectFile,           N_NANDWRITE | N_EMUNAND | F_IMPORT },
            { "Inyectar copia de certs.db",              &InjectFile,           N_NANDWRITE | N_EMUNAND | F_CERTS },
            { "Inyectar copia de SecureInfo_A",          &InjectFile,           N_NANDWRITE | N_EMUNAND | F_SECUREINFO },
            { "Inyectar copia de LocalFriendCodeSeed_B", &InjectFile,           N_NANDWRITE | N_EMUNAND | F_LOCALFRIEND },
            { "Inyectar copia de movable.sed",           &InjectFile,           N_NANDWRITE | N_EMUNAND | F_MOVABLE },
            { "Inyectar copia de seedsave.bin",          &InjectFile,           N_NANDWRITE | N_EMUNAND | F_SEEDSAVE },
            { "Inyectar copia de nagsave.bin",           &InjectFile,           N_NANDWRITE | N_EMUNAND | F_NAGSAVE },
            { "Inyectar copia de nnidsave.bin",          &InjectFile,           N_NANDWRITE | N_EMUNAND | F_NNIDSAVE },
            { "Inyectar copia de friendsave.bin",        &InjectFile,           N_NANDWRITE | N_EMUNAND | F_FRIENDSAVE }
        }
    },
    {
        "Opciones de 'miscelaneo' (SysNAND)", 5, // ID 10
        {

            { "Copiar aplicacion 'Salud y Seguridad'",           &DumpHealthAndSafety,   0 },
            { "Inyectar aplicacion 'Salud y Seguridad'",         &InjectHealthAndSafety, N_NANDWRITE },
            { "Actualizar SeedDB",                &UpdateSeedDb,          0 },
            { "Copia de los NCCH FIRMs",              &DumpNcchFirms,         0 },
            { "Descifrar FIRM ARM9",          &DecryptFirmArm9File,   0 }
        }
    },
    {
        "Opciones de 'miscelaneo' (EmuNAND)", 5, // ID 11
        {

            { "Copiar aplicacion 'Salud y Seguridad'",           &DumpHealthAndSafety,   N_EMUNAND },
            { "Inyectar aplicacion 'Salud y Seguridad'",         &InjectHealthAndSafety, N_NANDWRITE | N_EMUNAND },
            { "Actualizar SeedDB",                &UpdateSeedDb,          N_EMUNAND },
            { "Copia de los NCCH FIRMs",              &DumpNcchFirms,         N_EMUNAND },
            { "Descifrar FIRM ARM9",          &DecryptFirmArm9File,   0 }
        }
    },
    {
        NULL, 0, { { 0 } } // empty menu to signal end
    }
};


void Reboot()
{
    i2cWriteRegister(I2C_DEV_MCU, 0x20, 1 << 2);
    while(true);
}


void PowerOff()
{
    i2cWriteRegister(I2C_DEV_MCU, 0x20, 1 << 0);
    while (true);
}


u32 InitializeD9()
{
    u32 errorlevel = 0; // 0 -> none, 1 -> autopause, 2 -> critical

    ClearScreenFull(true, true);
    DebugClear();
    #ifndef BUILD_NAME
    Debug("-- Decrypt9 --");
    #else
    Debug("-- %s --", BUILD_NAME);
    #endif

    // a little bit of information about the current menu
    if (sizeof(menu)) {
        u32 n_submenus = 0;
        u32 n_features = 0;
        for (u32 m = 0; menu[m].n_entries; m++) {
            n_submenus = m;
            for (u32 e = 0; e < menu[m].n_entries; e++)
                n_features += (menu[m].entries[e].function) ? 1 : 0;
        }
        Debug("Contando %u submenus y %u opciones", n_submenus, n_features);
    }

    Debug("Inicializando, presiona L+R para pausar");
    Debug("");

    if (InitFS()) {
        Debug("Inicializando la tarjeta SD... éxito");
        FileGetData("d9logo.bin", BOT_SCREEN0, 320 * 240 * 3, 0);
        memcpy(BOT_SCREEN1, BOT_SCREEN0, 320 * 240 * 3);
        SetupSector0x96Key0x11(); // Sector0x96 key - no effect on error level
        if (SetupTwlKey0x03() != 0) // TWL KeyX / KeyY
            errorlevel = 2;
        if ((GetUnitPlatform() == PLATFORM_N3DS) && (SetupCtrNandKeyY0x05() != 0))
            errorlevel = 2; // N3DS CTRNAND KeyY
        if (LoadKeyFromFile(0x25, 'X', NULL)) // NCCH 7x KeyX
            errorlevel = (errorlevel < 1) ? 1 : errorlevel;
        if (GetUnitKeysType() != KEYS_DEVKIT) { // don't even try 0x18 / 0x1B on devkits
            if (LoadKeyFromFile(0x18, 'X', NULL)) // NCCH Secure3 KeyX
                errorlevel = (errorlevel < 1) ? 1 : errorlevel;
            if (LoadKeyFromFile(0x1B, 'X', NULL)) // NCCH Secure4 KeyX
                errorlevel = (errorlevel < 1) ? 1 : errorlevel;
        }
        Debug("Finalizando inicializacion...");
        RemainingStorageSpace();
    } else {
        Debug("Inicializando tarjeta SD... fallo");
            errorlevel = 2;
    }
    Debug("");
    Debug("Inicializacion: %s", (errorlevel == 0) ? "¡éxito!" : (errorlevel == 1) ? "fallo parcial" : "¡fallo!");

    if (((~HID_STATE & BUTTON_L1) && (~HID_STATE & BUTTON_R1)) || (errorlevel > 1)) {
        Debug("(A para %s)", (errorlevel > 1) ? "salir" : "continuar");
        while (!(InputWait() & BUTTON_A));
    }

    return errorlevel;
}


int main()
{
    u32 menu_exit = MENU_EXIT_REBOOT;

    if (InitializeD9() <= 1) {
        menu_exit = ProcessMenu(menu, SUBMENU_START);
    }
    DeinitFS();

    (menu_exit == MENU_EXIT_REBOOT) ? Reboot() : PowerOff();
    return 0;
}
