

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

class widget;
    

//=== Cpp2 type definitions and function declarations ===========================

class widget {
    private: int val {0}; 
    public: explicit widget(cpp2::in<int> i);
#line 3 "variadics.cpp2"
    public: auto operator=(cpp2::in<int> i) -> widget& ;

public: [[nodiscard]] auto operator<=>(widget const& that) const& -> std::strong_ordering = default;
public: widget(widget const& that);
public: auto operator=(widget const& that) -> widget& ;
public: widget(widget&& that) noexcept;
public: auto operator=(widget&& that) noexcept -> widget& ;
public: explicit widget();

#line 4 "variadics.cpp2"
};

auto main() -> int;
    

#line 11 "variadics.cpp2"
template<typename T> auto test() -> void;
    

//=== Cpp2 function definitions =================================================


#line 3 "variadics.cpp2"
    widget::widget(cpp2::in<int> i)
                                      : val{ i }
#line 3 "variadics.cpp2"
    {}
#line 3 "variadics.cpp2"
    auto widget::operator=(cpp2::in<int> i) -> widget& {
                                      val = i;
                                      return *this;
#line 3 "variadics.cpp2"
    }


    widget::widget(widget const& that)
                                : val{ that.val }{}

auto widget::operator=(widget const& that) -> widget& {
                                val = that.val;
                                return *this;}
widget::widget(widget&& that) noexcept
                                : val{ std::move(that).val }{}
auto widget::operator=(widget&& that) noexcept -> widget& {
                                val = std::move(that).val;
                                return *this;}
widget::widget(){}
#line 6 "variadics.cpp2"
auto main() -> int{
    test<widget>();
    std::cout << test.name << std::endl;
}

template<typename T> auto test() -> void{
    //  should be default constructible
    T a {}; 

    //  widget should be comparable
    T b {2}; 
    if ((cpp2::cmp_less(std::move(a),std::move(b)))) {
        std::cout << "less ";
    }
    else {
        std::cout << "more ";
    }
}

