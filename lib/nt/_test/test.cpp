#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../prime/sieve.hpp"
#include "../prime/test.hpp"
#include "../nt.hpp"

TEST_CASE( "Millar-Rabin" )
{
    REQUIRE( prime::test::mr( 0 ) == false );
    REQUIRE( prime::test::mr( 2 ) == true );
    REQUIRE( prime::test::mr( 61 ) == true );
    REQUIRE( prime::test::mr( 997 ) == true );
    REQUIRE( prime::test::mr( 340561 ) == false );
    REQUIRE( prime::test::mr( 4129075 ) == false);
    REQUIRE( prime::test::mr( 4129077 ) == false);
    REQUIRE( prime::test::mr( 4129087 ) == true);
    REQUIRE( prime::test::mr( 232250619601UL ) == false );
    REQUIRE( prime::test::mr( 456456456061UL ) == true );
}

TEST_CASE( "Fermat" )
{
    REQUIRE( prime::test::fermat( 0 ) == false );
    REQUIRE( prime::test::fermat( 2 ) == true );
    REQUIRE( prime::test::fermat( 61 ) == true );
    REQUIRE( prime::test::fermat( 997 ) == true );
    REQUIRE( prime::test::fermat( 340561 ) == false );
    REQUIRE( prime::test::fermat( 4129075 ) == false);
    REQUIRE( prime::test::fermat( 4129077 ) == false);
    REQUIRE( prime::test::fermat( 4129087 ) == true);
    REQUIRE( prime::test::fermat( 232250619601UL ) == false );
    REQUIRE( prime::test::fermat( 456456456061UL ) == true );
}

TEST_CASE( "Naive" )
{
    REQUIRE( prime::test::naive( 0 ) == false );
    REQUIRE( prime::test::naive( 2 ) == true );
    REQUIRE( prime::test::naive( 61 ) == true );
    REQUIRE( prime::test::naive( 997 ) == true );
    REQUIRE( prime::test::naive( 340561 ) == false );
    REQUIRE( prime::test::naive( 4129075 ) == false);
    REQUIRE( prime::test::naive( 4129077 ) == false);
    REQUIRE( prime::test::naive( 4129087 ) == true);
    REQUIRE( prime::test::naive( 232250619601UL ) == false );
    REQUIRE( prime::test::naive( 456456456061UL ) == true );
}
