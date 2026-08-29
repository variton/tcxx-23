
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include <err_utils.h>
#include <errty.h>
#include <intervalerr.h>
#include <ncnm.h>

/*
 * Define a class that possess an error info
 * and a way for other class to find this error type
 * at compile time
 */

enum class DecoyError { ValueError };

ERR_DEFINE_ERROR_INFO(DecoyError, DecoyErrorInfo);

class Decoy : public core::NCNM<Decoy> {
public:
  explicit Decoy(int id) noexcept : id_{id} {}
  ~Decoy() = default;

  std::expected<void, DecoyErrorInfo> compare_id(int val) const noexcept {
    if (val == id_) {
      return err::unexpected(DecoyError::ValueError, "value is not valid");
    }
    return {};
  };

private:
  int id_;
};

enum class ClientError { ValueError };

ERR_DEFINE_ERROR_INFO(ClientError, ClientErrorInfo);

template <typename T, typename ERR>
class Client : public core::NCNM<Client<T, ERR>> {

public:
  explicit Client(int id) noexcept : id_{id} {}
  ~Client() = default;

  std::expected<void, ERR> compare_id(int val) const noexcept {
    T t{id_};
    auto res = t.compare_id(val);
    if (!res.has_value()) {
      return err::propagate(res);
    }
    return {};
  }

private:
  int id_;
};

enum class XClientError { ValueError };

ERR_DEFINE_ERROR_INFO(XClientError, XClientErrorInfo);

template <typename T, typename ERR>
class XClient : public core::NCNM<XClient<T, ERR>> {

public:
  explicit XClient(int id) noexcept : id_{id} {}
  ~XClient() = default;

  std::expected<void, ERR> compare_id(int val) const noexcept {
    T t{id_};
    auto res = t.compare_id(val);
    if (!res.has_value()) {
      return err::propagate(res, XClientError::ValueError);
    }
    return {};
  }

private:
  int id_;
};

TEST_CASE("IntervalScannerError topology enum class") {
  static_assert(topology::ErrorInfoTy<math::IntervalErrorInfo>);
  CHECK(true);
}

TEST_CASE("DefineErrorInfo macro") {
  enum class ObliviousError {};
  ERR_DEFINE_ERROR_INFO(ObliviousError, ObliviousErrorInfo);
  static_assert(
      std::same_as<ObliviousErrorInfo, err::ErrorInfo<ObliviousError>>);
  CHECK(true);
}

TEST_CASE("Propagate error with target") {
  XClient<Decoy, XClientErrorInfo> d{1};
  auto res = d.compare_id(1);
  CHECK(!res.has_value());
  CHECK(res.error().type == XClientError::ValueError);
  CHECK(res.error().message == "value is not valid");
}

TEST_CASE("Propagate error without target") {
  Client<Decoy, DecoyErrorInfo> d{1};
  auto res = d.compare_id(1);
  CHECK(!res.has_value());
  CHECK(res.error().type == DecoyError::ValueError);
  CHECK(res.error().message == "value is not valid");
}
