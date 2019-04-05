
#include <gtest/gtest.h>

#include "tgl/tgl_gl.h"

#include "tgl/base.h"
#include "tmc/mc_player.h"
#include "tmc/chunk_spawn.h"

#include <cereal/archives/binary.hpp>
#include <cereal/archives/xml.hpp>
#include <cereal/archives/json.hpp>

#include <boost/serialization/export.hpp>

BOOST_CLASS_EXPORT(tmc::ChunkSpawn)
BOOST_SERIALIZATION_ASSUME_ABSTRACT(tgl::Actor)
//BOOST_CLASS_EXPORT(tmc::Player)

struct BaseTest : testing::Test
{
  tgl::Base * base;
  tgl::Base * base2;
  tmc::ChunkSpawn * chunk_spawn;
  tmc::ChunkSpawn * chunk_spawn2;
  tmc::Player * mc_player;
  tmc::Player * mc_player2;
  //std::basic_stringstream<char> s;
  std::stringstream s;
  
  BaseTest()
  {
    base = new tgl::Base();
    chunk_spawn = new tmc::ChunkSpawn();
    mc_player = new tmc::Player();
    base->init();
    
    base->add_actor(chunk_spawn);
    base->add_actor(mc_player);
    tgl::Actor::_id_counter = 1;
    base2 = new tgl::Base();
    chunk_spawn2 = new tmc::ChunkSpawn();
    mc_player2 = new tmc::Player();
    base2->init();
    
    base2->add_actor(chunk_spawn2);
    base2->add_actor(mc_player2);
    
  }
  virtual ~BaseTest()
  {
    delete base;
  }
};

TEST_F(BaseTest, Serialize)
{
    base->actors[0]->set_pos(glm::vec3(1,2,3));
    glm::mat4 init_mat;
    init_mat[1][3] = 2.134;
    init_mat[0][2] = -2.45;
    base->actors[1]->set_rot(init_mat);
    
    EXPECT_FALSE(*base == *base2);
    std::ofstream ofs("filename");
  
    // save data to archive
    {
        boost::archive::text_oarchive oa(ofs);
        // write class instance to archive
        oa << *base;
    	// archive and stream closed when destructors are called
    }

    {
        // create and open an archive for input
        std::ifstream ifs("filename");
        boost::archive::text_iarchive ia(ifs);
        // read class state from archive
        ia >> *base2;
        // archive and stream closed when destructors are called
    }
    std::cout << "LENGTHS: " << base->actors.size() << ", " << base2->actors.size() << "\n";
    std::cout << "IDs: " << base->actors[0]->id << ", " << base2->actors[0]->id << "\n";
    std::cout << "IDs: " << base->actors[1]->id << ", " << base2->actors[1]->id << "\n";
    
    EXPECT_TRUE(*base == *base2);
}

#ifdef _UNIT_TEST
int main(int ac, char* av[])
#else
int main2(int ac, char* av[])
#endif
{
  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}
