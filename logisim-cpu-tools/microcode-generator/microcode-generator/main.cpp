#include <fstream>
#include <iomanip>

constexpr unsigned int NOP = 0x00;

constexpr unsigned int MOVAImm = 0x01;
constexpr unsigned int MOVBImm = 0x02;
constexpr unsigned int MOVCImm = 0x03;
constexpr unsigned int MOVDImm = 0x04;

constexpr unsigned int MOVAB = 0x05;
constexpr unsigned int MOVAC = 0x06;
constexpr unsigned int MOVAD = 0x07;
constexpr unsigned int MOVBA = 0x08;
constexpr unsigned int MOVBC = 0x09;
constexpr unsigned int MOVBD = 0x0A;
constexpr unsigned int MOVCA = 0x0B;
constexpr unsigned int MOVCB = 0x0C;
constexpr unsigned int MOVCD = 0x0D;
constexpr unsigned int MOVDA = 0x0E;
constexpr unsigned int MOVDB = 0x0F;
constexpr unsigned int MOVDC = 0x10;

constexpr unsigned int ADDAB = 0x81;
constexpr unsigned int ADDAC = 0x82;
constexpr unsigned int ADDAD = 0x83;
constexpr unsigned int ADDBA = 0x84;
constexpr unsigned int ADDBC = 0x85;
constexpr unsigned int ADDBD = 0x86;
constexpr unsigned int ADDCA = 0x87;
constexpr unsigned int ADDCB = 0x88;
constexpr unsigned int ADDCD = 0x89;
constexpr unsigned int ADDDA = 0x8A;
constexpr unsigned int ADDDB = 0x8B;
constexpr unsigned int ADDDC = 0x8C;

enum Stage1ControlBits
{
    S1_REA_SEL0 = 1 << 0,
    S1_REA_SEL1 = 1 << 1,
    S1_REB_SEL0 = 1 << 2,
    S1_REB_SEL1 = 1 << 3,
    S1_WEImm    = 1 << 4,
};

enum Stage2ControlBits
{
    S2_WE_SEL0 = 1 << 0,
    S2_WE_SEL1 = 1 << 1,
    S2_WE_SEL2 = 1 << 2,
    S2_RE_SEL0 = 1 << 3,
    S2_RE_SEL1 = 1 << 4,
    S2_RE_SEL2 = 1 << 5,
};

enum RegIndex
{
    RegAWE = 0,
    RegBWE = 1,
    RegCWE = 2,
    RegDWE = 3,
    RegARE = 0 << 3,
    RegBRE = 1 << 3,
    RegCRE = 2 << 3,
    RegDRE = 3 << 3,
    RegImmRE = 4 << 3
};

unsigned int getStage1Byte(unsigned int opcode)
{
    switch (opcode)
    {
    case NOP: return 0x00;

    case MOVAImm: return S1_WEImm;
    case MOVBImm: return S1_WEImm;
    case MOVCImm: return S1_WEImm;
    case MOVDImm: return S1_WEImm;

    case MOVAB:
    case MOVAC:
    case MOVAD:
    case MOVBA:
    case MOVBC:
    case MOVBD:
    case MOVCA:
    case MOVCB:
    case MOVCD:
    case MOVDA:
    case MOVDB:
    case MOVDC:

    case ADDAB:
    case ADDAC:
    case ADDAD:
    case ADDBA:
    case ADDBC:
    case ADDBD:
    case ADDCA:
    case ADDCB:
    case ADDCD:
    case ADDDA:
    case ADDDB:
    case ADDDC:
    }

    return 0;
}

unsigned int getStage2Byte(unsigned int opcode)
{
    switch (opcode)
    {
    case NOP: return 0x00;

    case MOVAImm: return RegAWE | RegImmRE;
    case MOVBImm: return RegBWE | RegImmRE;
    case MOVCImm: return RegCWE | RegImmRE;
    case MOVDImm: return RegDWE | RegImmRE;

    case MOVAB:
    case MOVAC:
    case MOVAD:
    case MOVBA:
    case MOVBC:
    case MOVBD:
    case MOVCA:
    case MOVCB:
    case MOVCD:
    case MOVDA:
    case MOVDB:
    case MOVDC:

    case ADDAB:
    case ADDAC:
    case ADDAD:
    case ADDBA:
    case ADDBC:
    case ADDBD:
    case ADDCA:
    case ADDCB:
    case ADDCD:
    case ADDDA:
    case ADDDB:
    case ADDDC:
    }

    return 0;
}

int main()
{
    {
        std::ofstream fout{ "stage1.microcode" };
        fout << "v3.0 hex words addressed";
        fout << std::hex;

        for (unsigned int addr = 0; addr < 0x100; ++addr)
        {
            if ((addr & 0xF) == 0)
                fout << '\n' << std::setfill('0') << std::setw(2) << addr << ":";

            fout << ' ' << std::setfill('0') << std::setw(2) << getStage1Byte(addr);
        }

        fout << '\n';
        fout.close();
    }
    {
        std::ofstream fout{ "stage2.microcode" };
        fout << "v3.0 hex words addressed";
        fout << std::hex;

        for (unsigned int addr = 0; addr < 0x100; ++addr)
        {
            if ((addr & 0xF) == 0)
                fout << '\n' << std::setfill('0') << std::setw(2) << addr << ":";

            fout << ' ' << std::setfill('0') << std::setw(2) << getStage2Byte(addr);
        }

        fout << '\n';
        fout.close();
    }

    return 0;
}
