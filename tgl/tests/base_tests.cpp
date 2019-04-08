
#include <gtest/gtest.h>

#include "tgl/tgl_gl.h"

#include "tgl/base.h"
#include "tmc/mc_player.h"
#include "tmc/chunk_spawn.h"

#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/polymorphic.hpp>

#include <boost/serialization/export.hpp>

struct BaseTest : testing::Test
{
  std::unique_ptr<tgl::Base> base;
  std::unique_ptr<tgl::Base> base2;
  std::shared_ptr<tgl::Actor> chunk_spawn;
  std::shared_ptr<tgl::Actor> chunk_spawn2;
  std::shared_ptr<tgl::Actor> mc_player;
  std::shared_ptr<tgl::Actor> mc_player2;
  //std::basic_stringstream<char> s;
  std::stringstream s;
  
  BaseTest()
  {
    base = std::unique_ptr<tgl::Base>(new tgl::Base());
    chunk_spawn = std::make_shared<tmc::ChunkSpawn>();
    mc_player = std::make_shared<tmc::Player>();
    base->init();
    
    base->add_actor<tmc::ChunkSpawn>();
    base->add_actor<tmc::Player>();
    tgl::Actor::_id_counter = 1;
    base2 = std::unique_ptr<tgl::Base>(new tgl::Base());
    chunk_spawn2 = std::make_shared<tmc::ChunkSpawn>();
    mc_player2 = std::make_shared<tmc::Player>();
    base2->init();
    
    base2->add_actor<tmc::ChunkSpawn>();
    base2->add_actor<tmc::Player>();
    
  }
  virtual ~BaseTest()
  {
    base.release();
  }
};

TEST_F(BaseTest, Serialize)
{
    std::vector<std::unique_ptr<tgl::Actor>> actors;
    actors.push_back(std::unique_ptr<tgl::Actor>(new tmc::ChunkSpawn));
    actors.push_back(std::unique_ptr<tgl::Actor>(new tmc::ChunkSpawn));
    actors.push_back(std::unique_ptr<tgl::Actor>(new tmc::Player));
  
    base->actors[0]->set_pos(glm::vec3(1,2,3));
    glm::mat4 init_mat;
    init_mat[1][3] = 2.134;
    init_mat[0][2] = -2.45;
    base->actors[1]->set_rot(init_mat);
    std::unique_ptr<tgl::Actor> cs1(new tmc::ChunkSpawn);
    std::unique_ptr<tgl::Actor> cs2(new tmc::ChunkSpawn);
    std::stringstream os;
    EXPECT_FALSE(*base == *base2);
    {
      //std::ofstream os( "polymorphism_test.Binary" );
      
      cereal::BinaryOutputArchive oarchive( os );
  
      oarchive( base );
    }
  
    {
      //std::ifstream is( "polymorphism_test.Binary" );
      std::stringstream is(os.str());
      cereal::BinaryInputArchive iarchive( is );
  
      iarchive( base2 );
    }
    
    EXPECT_TRUE(*base == *base2);
}

TEST_F(BaseTest, AddActor)
{
    std::shared_ptr<tgl::Actor> new_actor = 
              base->add_actor<tgl::Actor>(glm::vec3(5, 6, 7));
    EXPECT_EQ(new_actor->get_pos(), base->actors.back()->get_pos());
    EXPECT_EQ(new_actor->get_pos(), glm::vec3(5, 6, 7));
}