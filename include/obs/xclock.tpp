
namespace obs {

template <typename CLOCK, typename PRECISION>
Xclock<CLOCK, PRECISION>::Xclock() noexcept
    : started_(false),
      time_elapsed_("0 s") {}

template <typename CLOCK, typename PRECISION>
Xclock<CLOCK, PRECISION>::~Xclock() = default;

template <typename CLOCK, typename PRECISION>
void Xclock<CLOCK, PRECISION>::operator()() noexcept {
  (!started_)? start(): stop();   
}

template <typename CLOCK, typename PRECISION>
std::string_view Xclock<CLOCK, PRECISION>::elapsed() const {
    return time_elapsed_;
}

template <typename CLOCK, typename PRECISION>
void Xclock<CLOCK, PRECISION>::start() noexcept {
    started_ = true;
    begin_ = std::chrono::time_point_cast<PRECISION>(CLOCK::now());
}

template <typename CLOCK, typename PRECISION>
void Xclock<CLOCK, PRECISION>::stop() noexcept {
    end_ = std::chrono::time_point_cast<PRECISION>(CLOCK::now());
    started_ = false;
    measure();
}

template <typename CLOCK, typename PRECISION>
void Xclock<CLOCK, PRECISION>::measure() noexcept {
  auto time_=std::chrono::duration_cast<PRECISION>(end_-begin_).count();
  time_elapsed_=std::to_string(time_)+" s";
}

template<>
void Xclock<std::chrono::high_resolution_clock,std::chrono::nanoseconds>::measure() noexcept{
    auto time_=std::chrono::duration_cast<std::chrono::nanoseconds>(end_-begin_).count();
    time_elapsed_=std::to_string(time_)+" ns";
}

template<>
void Xclock<std::chrono::high_resolution_clock,std::chrono::microseconds>::measure() noexcept{
    auto time_=std::chrono::duration_cast<std::chrono::microseconds>(end_-begin_).count();
    time_elapsed_=std::to_string(time_)+" µs";
}

template<>
void Xclock<std::chrono::high_resolution_clock,std::chrono::milliseconds>::measure() noexcept{
    auto time_=std::chrono::duration_cast<std::chrono::milliseconds>(end_-begin_).count();
    time_elapsed_=std::to_string(time_)+" ms";
}

using s_clock = Xclock<std::chrono::system_clock,std::chrono::seconds>;
using milli_c=Xclock<std::chrono::high_resolution_clock,std::chrono::milliseconds>;
using micro_c=Xclock<std::chrono::high_resolution_clock,std::chrono::microseconds>;
using nano_c=Xclock<std::chrono::high_resolution_clock,std::chrono::nanoseconds>;

}
