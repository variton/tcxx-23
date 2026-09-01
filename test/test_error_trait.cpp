
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include <err_utils.h>
#include <error_trait.h>
#include <ncnm.h>
#include <type_traits>

template <typename T> using Default = core::NCNM<T>;

enum class ServerError { DiskError, MemoryError, NetworkError, SystemError };

ERR_DEFINE_ERROR_INFO(ServerError, ServerErrorInfo);

class Server : public core::NCNM<Server>,
               public err::ErrorTrait<ServerErrorInfo> {
public:
  explicit Server(int workers) noexcept : workers_{workers} {}
  ~Server() = default;

  std::expected<void, ErrTypeInfo> compare_id(int jobs) const noexcept {
    if (jobs == workers_) {
      return err::unexpected(ErrType::DiskError, "not enough disk on server");
    }
    return {};
  };

private:
  int workers_;
};

enum class ClientError { RequestError };

ERR_DEFINE_ERROR_INFO(ClientError, ClientErrorInfo);

class Client : public core::NCNM<Client> {

public:
  explicit Client(int id) noexcept : id_{id} {}
  ~Client() = default;

  std::expected<void, ServerErrorInfo> compare_id(int val) const noexcept {
    Server server{2};
    auto res = server.compare_id(val);
    if (!res.has_value()) {
      return err::propagate(res);
    }
    return {};
  }

private:
  int id_;
};

enum class XClientError { RequestError };

ERR_DEFINE_ERROR_INFO(XClientError, XClientErrorInfo);

template <typename T> class XClient : public core::NCNM<XClient<T>> {

public:
  explicit XClient(int id) noexcept : id_{id} {}
  ~XClient() = default;

  std::expected<void, typename T::ErrTypeInfo>
  compare_id(int val) const noexcept {
    T t{2};
    auto res = t.compare_id(val);
    if (!res.has_value()) {
      return err::propagate(res);
    }
    return {};
  }

private:
  int id_;
};

TEST_CASE("Server Error Type & Info") {
  using Error = Server::ErrType;
  using ErrorInfo = Server::ErrTypeInfo;
  static_assert(std::same_as<Error, ServerError>);
  static_assert(std::same_as<ErrorInfo, ServerErrorInfo>);
}

TEST_CASE("Propagate error with target") {
  Client client{2};
  auto res = client.compare_id(2);
  CHECK(!res.has_value());
  CHECK(res.error().type == ServerError::DiskError);
  CHECK(res.error().message == "not enough disk on server");
}

TEST_CASE("Propagate error with target and compile time template Info") {
  XClient<Server> client{2};
  auto res = client.compare_id(2);
  CHECK(!res.has_value());
  CHECK(res.error().type == ServerError::DiskError);
  CHECK(res.error().message == "not enough disk on server");
}
