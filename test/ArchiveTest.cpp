#include <gtest/gtest.h>
#include <fstream>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#include "Archive.hpp"

#include "Socket.hpp"

TEST(ArchiveTest, CompressTest) {
  std::fstream fs("1", std::fstream::out);
  fs << 1 << std::endl;
  fs.close();
  fs.open("2", std::fstream::out);
  fs << 2 << std::endl;
  fs.close();

  int fd = open("test.tar", O_TRUNC|O_WRONLY, 0644);

  DockerClientpp::Utility::Archive ac({"1", "2"});
  ac.writeToFd(fd);

  //DockerClientpp::Socket s(DockerClientpp::UNIX, "/var/run/docker.sock");

}
