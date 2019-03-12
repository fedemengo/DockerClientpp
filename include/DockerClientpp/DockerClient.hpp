#ifndef DOCKER_CLIENT_PP_DOCKERCLIENT_H
#define DOCKER_CLIENT_PP_DOCKERCLIENT_H

#include "Archive.hpp"
#include "ExecRet.hpp"
#include "Response.hpp"
#include "SimpleHttpClient.hpp"
#include "defines.hpp"

namespace DockerClientpp {

/**
 * @brief Docker client class
 */
class DockerClient {
  /**
   * @brief Disallow copy
   */
  DockerClient(const DockerClient &) = delete;
  /**
   * @brief Disallow copy
   */
  DockerClient &operator=(const DockerClient &) = delete;

 public:
  DockerClient(DockerClient &&) = default;

  ~DockerClient();

 public:
  /**
   * @brief Constructor, create a socket file
   * @param type socket type that docker daemon use
   * @param path path to the docker daemon socket
   *        if type is TCP, path might be a IP to docker daemon server
   */
  DockerClient(const SOCK_TYPE type = UNIX,
               const string &path = "/var/run/docker.sock");

  /**
   * @brief Set Docker daemon API version
   *
   * The default api version is v1.24
   *
   * @param api api version to be set. e.g. api = "v1.24"
   */
  void setAPIVersion(const string &api);

  /**
   * @brief List all images
   *
   * Test Only!
   *
   * @return Images list in json format
   */
  string listImages();

  /**
   * @brief Create a new container based on existing image
   *
   * This does not mean that you can pass multiple commands to Cmd.
   * A valid command may look like this: `Cmd = {"ls", "-a", "-l"}`
   * If you want to run multiple commands in one run, consider using shell
   * script
   * e.g. `Cmd = {"bash", "-c", "mkdir test && cd test"}`
   *
   * @param config configuration
   * @param name container's name
   * @return container's id
   * @sa CreateContainerOption
   */
  string createContainer(const json &config, const string &name = "");

  /**
   * @brief Start a stopped or created container
   * @param identifier Container's ID or name
   */
  void startContainer(const string &identifier);

  /**
   * @brief Stop a running container
   * @param identifier Container's ID or name
   */
  void stopContainer(const string &identifier);

  /**
   * @brief Remove a container
   * @param identifier Container's ID or name
   * @param remove_volume remove the mounted volume or not
   * @param force force to remove a container, e.g. a running container
   * @param remove_link remove the associated link
   */
  void removeContainer(const string &identifier, bool remove_volume = false,
                       bool force = false, bool remove_link = false);

  /**
   * @brief Set up an exec running instance in a running container
   *
   * The execution won't start until a start command is executed on it
   *
   * @param identifier Container's ID or name
   * @param config configuration
   * @return Execution ID, needed when start a execution
   */
  string createExecution(const string &identifier, const json &config);

  /**
   * @brief Start a execution instance that is set up previously
   *
   * The first byte of the return value indicates output type
   * 0: stdin
   * 1: stdout
   * 2: stderr
   *
   * @param id Execution instance ID
   * @param config configuration
   * @return if Detach is false, return output
   */
  string startExecution(const string &id, const json &config = {});

  /**
   * @brief Get statistics for a execution instance
   *
   * @param id Execution instance ID
   * @return Execution stats
   */
  string getContainerStats(const string &id);
  
  /**
   * @brief Inspect a execution instance
   *
   * @param id Execution instance ID
   * @return Execution status
   */
  string inspectExecution(const string &id);

  /**
   * @brief Update the configurations of already created container 
   *
   * @param identifier Container's ID or name
   * @param config configuration
   * @return 
   */

  void updateContainer(const std::string &id, const json &config);

  /**
   * @brief Execute a command in a running container, like `docker exec`
   * command
   *
   * For reference of parameters cmd see createContainer()
   *
   * @param identifier Container's ID or name
   * @param cmd Executing command with parameters in vector
   * @return
   * @sa createContainer()
   */
  ExecRet executeCommand(const string &identifier, const vector<string> &cmd);

  /**
   * @brief Put files to container
   *
   * @param identifier container's id or name
   * @param files files need to be put
   * @param path location in the container
   */
  void putFiles(const string &identifier, const vector<string> &files,
                const string &path);

  /**
   * @brief Get file to container
   *
   * @param identifier container's id or name
   * @param file file in the container
   * @param path location that the file to be stored in
   */
  void getFile(const string &identifier, const string &file,
               const string &path);

  json downloadImage(const string &imageName, const string &tag={}, const json &config={});

	/**
	 * @brief Create a new image from container
	 * 
	 * @param identifier container's id or name
	 * @param description of the commit
	 * @param tag name for the image
	 * @config configuration parameter for creating the image
	 */
	json commitImage(const string &idOrName, const string &repo, const string &message, const string &tag={}, const json &config={});

  void killContainer(const std::string &idOrName);
  
  int waitContainer(const std::string &idOrName);
  
  string getLogs(const string &id,bool stdoutFlag=true, bool stderrFlag=true, int tail=-1);

  string inspectContainer(const string &id) ;

  string getLongId(const std::string &name);
 private:
  class Impl;
  unique_ptr<Impl> m_impl;
};
}  // namespace DockerClientpp

#endif /* DOCKER_CLIENT_PP_DOCKERCLIENT_H */
