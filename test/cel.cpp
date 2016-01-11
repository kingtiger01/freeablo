#include <gtest/gtest.h>

#include <cel/celfile.h>
#include <faio/faio.h>
#include <misc/md5.h>

#include <iostream>
#include <string>

std::string hashCelFrame(const Cel::CelFrame& frame)
{
    size_t size = frame.mWidth * frame.mHeight * sizeof(Cel::Colour);

    Misc::md5_byte_t* buff = (Misc::md5_byte_t*)&frame[0][0];
    
    Misc::md5_state_t state;
    Misc::md5_byte_t digest[16];

    md5_init(&state);
    md5_append(&state, buff, size);
    md5_finish(&state, digest);

    std::stringstream s;

    for(size_t i = 0; i < 16; i++)
       s << std::hex << std::setw(2) << std::setfill('0') << (int)digest[i];

    return s.str();
}

TEST (Cel, TestOpen) 
{ 
    Cel::CelFile cel("Towners/TownBoy/PegKid1.CEL");
    std::cerr << "asdasdasd " << hashCelFrame(cel[0]) << std::endl;
    ASSERT_EQ (1.0, 0.0);
}

int main(int argc, char **argv) 
{
    FAIO::init();    

    ::testing::InitGoogleTest(&argc, argv);
    int retval = RUN_ALL_TESTS();

    FAIO::quit();

    return retval;
}
