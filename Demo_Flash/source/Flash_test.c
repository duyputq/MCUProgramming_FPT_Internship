#include <MKE16Z4.h>

//xoa
void Erase_Sector(uint32_t Address)
{

//check dieu kien dau vao
	//tai sao? truoc cau lenh vao erase thi minh khong biet se co command khac
	//co mot so ham khong can doi de hoan thanh
	//cho nen phai while de bao ve an toan
	// wait previous command finish
	while (FTFA->FSTAT == 0x00);

	// clear previous cmd error
	if (FTFA->FSTAT != 0x80)
	{
		FTFA->FSTAT = 0x30; // Clear 2 error flag
	}

//code chinh
	//thanh ghi FCCOB co 12 bytes
	// Erase all bytes in a program flash sector
	// xoa tat ca byte trong flash sector
	//follow the tai lieu, cai bang table 13-13 phan erase
	FTFA->FCCOB0 = 0x09;  // command erase
	FTFA->FCCOB1 = (Address >> 16) & 0xFF;
	FTFA->FCCOB2 = (Address >> 8) & 0xFF;
	FTFA->FCCOB3 = (Address >> 0) & 0xFF;

	// run command
	FTFA->FSTAT = 0x80;

	// wait command finish
	while (FTFA->FSTAT == 0x00);

}

//write
//viet giong erase, quy trinh van the
//sua command thoi
void Program_LongWord(uint32_t Address, uint8_t *Data)
{
	// wait previous command finish
	while (FTFA->FSTAT == 0x00);

	// clear previous cmd error
	if (FTFA->FSTAT != 0x80)
	{
		FTFA->FSTAT = 0x30; // Clear 2 error flag
	}

	// Flash 4 bytes in a program flash sector
	FTFA->FCCOB0 = 0x06;  // command erase
	FTFA->FCCOB1 = (Address >> 16) & 0xFF;
	FTFA->FCCOB2 = (Address >> 8) & 0xFF;
	FTFA->FCCOB3 = (Address >> 0) & 0xFF;

	//write data
	FTFA->FCCOB4 = Data[0];
	FTFA->FCCOB5 = Data[1];
	FTFA->FCCOB6 = Data[2];
	FTFA->FCCOB7 = Data[3];

	// run command
	FTFA->FSTAT = 0x80;

	// wait command finish
	while (FTFA->FSTAT == 0x00);

}

uint32_t Read_Flash_Address(uint32_t Address)
{
	return *(volatile uint32_t *)Address;
}

int main (){
	uint8_t data[4] = {0x01, 0x02, 0x03, 0x04};

	Program_LongWord(0xA000,data);

	while(1){

	}


	return 0;
}
