#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../prime/sieve.hpp"
#include "../prime/test.hpp"
#include "../nt.hpp"

using namespace nt::prime::test;

TEST_CASE( "Millar-Rabin" )
{
    REQUIRE(mr( 0 ) == false );
    REQUIRE(mr( 2 ) == true );
    REQUIRE(mr( 61 ) == true );
    REQUIRE(mr( 997 ) == true );
    REQUIRE(mr( 340561 ) == false );
    REQUIRE(mr( 4129075 ) == false);
    REQUIRE(mr( 4129077 ) == false);
    REQUIRE(mr( 4129087 ) == true);
    REQUIRE(mr( 232250619601UL ) == false );
    REQUIRE(mr( 456456456061UL ) == true );
}

TEST_CASE( "Fermat" )
{
    REQUIRE(fermat( 0 ) == false );
    REQUIRE(fermat( 2 ) == true );
    REQUIRE(fermat( 61 ) == true );
    REQUIRE(fermat( 997 ) == true );
    REQUIRE(fermat( 340561 ) == false );
    REQUIRE(fermat( 4129075 ) == false);
    REQUIRE(fermat( 4129077 ) == false);
    REQUIRE(fermat( 4129087 ) == true);
    REQUIRE(fermat( 232250619601UL ) == false );
    REQUIRE(fermat( 456456456061UL ) == true );
}

TEST_CASE( "Naive" )
{
    REQUIRE(naive( 0 ) == false );
    REQUIRE(naive( 2 ) == true );
    REQUIRE(naive( 61 ) == true );
    REQUIRE(naive( 997 ) == true );
    REQUIRE(naive( 340561 ) == false );
    REQUIRE(naive( 4129075 ) == false);
    REQUIRE(naive( 4129077 ) == false);
    REQUIRE(naive( 4129087 ) == true);
    REQUIRE(naive( 232250619601UL ) == false );
    REQUIRE(naive( 456456456061UL ) == true );
}
