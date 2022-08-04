#include "souffle/CompiledSouffle.h"
#include "souffle/SignalHandler.h"
#include "souffle/SouffleInterface.h"
#include "souffle/datastructure/BTree.h"
#include "souffle/datastructure/EqRel.h"
#include "souffle/io/IOSystem.h"
#include <any>
namespace functors {
extern "C" {
}
} //namespace functors
namespace souffle::t_btree_i__0__2__1 {
struct Type {
static constexpr Relation::arity_type Arity = 1;
using t_tuple = Tuple<RamDomain, 1>;
struct t_comparator_0{
 int operator()(const t_tuple& a, const t_tuple& b) const {
  return (ramBitCast<RamSigned>(a[0]) < ramBitCast<RamSigned>(b[0])) ? -1 : (ramBitCast<RamSigned>(a[0]) > ramBitCast<RamSigned>(b[0])) ? 1 :(0);
 }
bool less(const t_tuple& a, const t_tuple& b) const {
  return (ramBitCast<RamSigned>(a[0]) < ramBitCast<RamSigned>(b[0]));
 }
bool equal(const t_tuple& a, const t_tuple& b) const {
return (ramBitCast<RamSigned>(a[0]) == ramBitCast<RamSigned>(b[0]));
 }
};
using t_ind_0 = btree_set<t_tuple,t_comparator_0>;
t_ind_0 ind_0;
using iterator = t_ind_0::iterator;
struct context {
t_ind_0::operation_hints hints_0_lower;
t_ind_0::operation_hints hints_0_upper;
};
context createContext() { return context(); }
bool insert(const t_tuple& t);
bool insert(const t_tuple& t, context& h);
bool insert(const RamDomain* ramDomain);
bool insert(RamDomain a0);
bool contains(const t_tuple& t, context& h) const;
bool contains(const t_tuple& t) const;
std::size_t size() const;
iterator find(const t_tuple& t, context& h) const;
iterator find(const t_tuple& t) const;
range<iterator> lowerUpperRange_0(const t_tuple& /* lower */, const t_tuple& /* upper */, context& /* h */) const;
range<iterator> lowerUpperRange_0(const t_tuple& /* lower */, const t_tuple& /* upper */) const;
range<t_ind_0::iterator> lowerUpperRange_2(const t_tuple& lower, const t_tuple& upper, context& h) const;
range<t_ind_0::iterator> lowerUpperRange_2(const t_tuple& lower, const t_tuple& upper) const;
range<t_ind_0::iterator> lowerUpperRange_1(const t_tuple& lower, const t_tuple& upper, context& h) const;
range<t_ind_0::iterator> lowerUpperRange_1(const t_tuple& lower, const t_tuple& upper) const;
bool empty() const;
std::vector<range<iterator>> partition() const;
void purge();
iterator begin() const;
iterator end() const;
void printStatistics(std::ostream& o) const;
};
} // namespace souffle::t_btree_i__0__2__1 
namespace souffle::t_btree_i__0__2__1 {
using t_ind_0 = Type::t_ind_0;
using iterator = Type::iterator;
using context = Type::context;
bool Type::insert(const t_tuple& t) {
context h;
return insert(t, h);
}
bool Type::insert(const t_tuple& t, context& h) {
if (ind_0.insert(t, h.hints_0_lower)) {
return true;
} else return false;
}
bool Type::insert(const RamDomain* ramDomain) {
RamDomain data[1];
std::copy(ramDomain, ramDomain + 1, data);
const t_tuple& tuple = reinterpret_cast<const t_tuple&>(data);
context h;
return insert(tuple, h);
}
bool Type::insert(RamDomain a0) {
RamDomain data[1] = {a0};
return insert(data);
}
bool Type::contains(const t_tuple& t, context& h) const {
return ind_0.contains(t, h.hints_0_lower);
}
bool Type::contains(const t_tuple& t) const {
context h;
return contains(t, h);
}
std::size_t Type::size() const {
return ind_0.size();
}
iterator Type::find(const t_tuple& t, context& h) const {
return ind_0.find(t, h.hints_0_lower);
}
iterator Type::find(const t_tuple& t) const {
context h;
return find(t, h);
}
range<iterator> Type::lowerUpperRange_0(const t_tuple& /* lower */, const t_tuple& /* upper */, context& /* h */) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<iterator> Type::lowerUpperRange_0(const t_tuple& /* lower */, const t_tuple& /* upper */) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<t_ind_0::iterator> Type::lowerUpperRange_2(const t_tuple& lower, const t_tuple& upper, context& h) const {
t_comparator_0 comparator;
int cmp = comparator(lower, upper);
if (cmp > 0) {
    return make_range(ind_0.end(), ind_0.end());
}
return make_range(ind_0.lower_bound(lower, h.hints_0_lower), ind_0.upper_bound(upper, h.hints_0_upper));
}
range<t_ind_0::iterator> Type::lowerUpperRange_2(const t_tuple& lower, const t_tuple& upper) const {
context h;
return lowerUpperRange_2(lower,upper,h);
}
range<t_ind_0::iterator> Type::lowerUpperRange_1(const t_tuple& lower, const t_tuple& upper, context& h) const {
t_comparator_0 comparator;
int cmp = comparator(lower, upper);
if (cmp == 0) {
    auto pos = ind_0.find(lower, h.hints_0_lower);
    auto fin = ind_0.end();
    if (pos != fin) {fin = pos; ++fin;}
    return make_range(pos, fin);
}
if (cmp > 0) {
    return make_range(ind_0.end(), ind_0.end());
}
return make_range(ind_0.lower_bound(lower, h.hints_0_lower), ind_0.upper_bound(upper, h.hints_0_upper));
}
range<t_ind_0::iterator> Type::lowerUpperRange_1(const t_tuple& lower, const t_tuple& upper) const {
context h;
return lowerUpperRange_1(lower,upper,h);
}
bool Type::empty() const {
return ind_0.empty();
}
std::vector<range<iterator>> Type::partition() const {
return ind_0.getChunks(400);
}
void Type::purge() {
ind_0.clear();
}
iterator Type::begin() const {
return ind_0.begin();
}
iterator Type::end() const {
return ind_0.end();
}
void Type::printStatistics(std::ostream& o) const {
o << " arity 1 direct b-tree index 0 lex-order [0]\n";
ind_0.printStats(o);
}
} // namespace souffle::t_btree_i__0__2__1 
namespace souffle::t_btree_iii__0_1_2__111 {
struct Type {
static constexpr Relation::arity_type Arity = 3;
using t_tuple = Tuple<RamDomain, 3>;
struct t_comparator_0{
 int operator()(const t_tuple& a, const t_tuple& b) const {
  return (ramBitCast<RamSigned>(a[0]) < ramBitCast<RamSigned>(b[0])) ? -1 : (ramBitCast<RamSigned>(a[0]) > ramBitCast<RamSigned>(b[0])) ? 1 :((ramBitCast<RamSigned>(a[1]) < ramBitCast<RamSigned>(b[1])) ? -1 : (ramBitCast<RamSigned>(a[1]) > ramBitCast<RamSigned>(b[1])) ? 1 :((ramBitCast<RamSigned>(a[2]) < ramBitCast<RamSigned>(b[2])) ? -1 : (ramBitCast<RamSigned>(a[2]) > ramBitCast<RamSigned>(b[2])) ? 1 :(0)));
 }
bool less(const t_tuple& a, const t_tuple& b) const {
  return (ramBitCast<RamSigned>(a[0]) < ramBitCast<RamSigned>(b[0]))|| ((ramBitCast<RamSigned>(a[0]) == ramBitCast<RamSigned>(b[0])) && ((ramBitCast<RamSigned>(a[1]) < ramBitCast<RamSigned>(b[1]))|| ((ramBitCast<RamSigned>(a[1]) == ramBitCast<RamSigned>(b[1])) && ((ramBitCast<RamSigned>(a[2]) < ramBitCast<RamSigned>(b[2]))))));
 }
bool equal(const t_tuple& a, const t_tuple& b) const {
return (ramBitCast<RamSigned>(a[0]) == ramBitCast<RamSigned>(b[0]))&&(ramBitCast<RamSigned>(a[1]) == ramBitCast<RamSigned>(b[1]))&&(ramBitCast<RamSigned>(a[2]) == ramBitCast<RamSigned>(b[2]));
 }
};
using t_ind_0 = btree_set<t_tuple,t_comparator_0>;
t_ind_0 ind_0;
using iterator = t_ind_0::iterator;
struct context {
t_ind_0::operation_hints hints_0_lower;
t_ind_0::operation_hints hints_0_upper;
};
context createContext() { return context(); }
bool insert(const t_tuple& t);
bool insert(const t_tuple& t, context& h);
bool insert(const RamDomain* ramDomain);
bool insert(RamDomain a0,RamDomain a1,RamDomain a2);
bool contains(const t_tuple& t, context& h) const;
bool contains(const t_tuple& t) const;
std::size_t size() const;
iterator find(const t_tuple& t, context& h) const;
iterator find(const t_tuple& t) const;
range<iterator> lowerUpperRange_000(const t_tuple& /* lower */, const t_tuple& /* upper */, context& /* h */) const;
range<iterator> lowerUpperRange_000(const t_tuple& /* lower */, const t_tuple& /* upper */) const;
range<t_ind_0::iterator> lowerUpperRange_111(const t_tuple& lower, const t_tuple& upper, context& h) const;
range<t_ind_0::iterator> lowerUpperRange_111(const t_tuple& lower, const t_tuple& upper) const;
bool empty() const;
std::vector<range<iterator>> partition() const;
void purge();
iterator begin() const;
iterator end() const;
void printStatistics(std::ostream& o) const;
};
} // namespace souffle::t_btree_iii__0_1_2__111 
namespace souffle::t_btree_iii__0_1_2__111 {
using t_ind_0 = Type::t_ind_0;
using iterator = Type::iterator;
using context = Type::context;
bool Type::insert(const t_tuple& t) {
context h;
return insert(t, h);
}
bool Type::insert(const t_tuple& t, context& h) {
if (ind_0.insert(t, h.hints_0_lower)) {
return true;
} else return false;
}
bool Type::insert(const RamDomain* ramDomain) {
RamDomain data[3];
std::copy(ramDomain, ramDomain + 3, data);
const t_tuple& tuple = reinterpret_cast<const t_tuple&>(data);
context h;
return insert(tuple, h);
}
bool Type::insert(RamDomain a0,RamDomain a1,RamDomain a2) {
RamDomain data[3] = {a0,a1,a2};
return insert(data);
}
bool Type::contains(const t_tuple& t, context& h) const {
return ind_0.contains(t, h.hints_0_lower);
}
bool Type::contains(const t_tuple& t) const {
context h;
return contains(t, h);
}
std::size_t Type::size() const {
return ind_0.size();
}
iterator Type::find(const t_tuple& t, context& h) const {
return ind_0.find(t, h.hints_0_lower);
}
iterator Type::find(const t_tuple& t) const {
context h;
return find(t, h);
}
range<iterator> Type::lowerUpperRange_000(const t_tuple& /* lower */, const t_tuple& /* upper */, context& /* h */) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<iterator> Type::lowerUpperRange_000(const t_tuple& /* lower */, const t_tuple& /* upper */) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<t_ind_0::iterator> Type::lowerUpperRange_111(const t_tuple& lower, const t_tuple& upper, context& h) const {
t_comparator_0 comparator;
int cmp = comparator(lower, upper);
if (cmp == 0) {
    auto pos = ind_0.find(lower, h.hints_0_lower);
    auto fin = ind_0.end();
    if (pos != fin) {fin = pos; ++fin;}
    return make_range(pos, fin);
}
if (cmp > 0) {
    return make_range(ind_0.end(), ind_0.end());
}
return make_range(ind_0.lower_bound(lower, h.hints_0_lower), ind_0.upper_bound(upper, h.hints_0_upper));
}
range<t_ind_0::iterator> Type::lowerUpperRange_111(const t_tuple& lower, const t_tuple& upper) const {
context h;
return lowerUpperRange_111(lower,upper,h);
}
bool Type::empty() const {
return ind_0.empty();
}
std::vector<range<iterator>> Type::partition() const {
return ind_0.getChunks(400);
}
void Type::purge() {
ind_0.clear();
}
iterator Type::begin() const {
return ind_0.begin();
}
iterator Type::end() const {
return ind_0.end();
}
void Type::printStatistics(std::ostream& o) const {
o << " arity 3 direct b-tree index 0 lex-order [0,1,2]\n";
ind_0.printStats(o);
}
} // namespace souffle::t_btree_iii__0_1_2__111 
namespace souffle::t_btree_ii__0_1__11__10 {
struct Type {
static constexpr Relation::arity_type Arity = 2;
using t_tuple = Tuple<RamDomain, 2>;
struct t_comparator_0{
 int operator()(const t_tuple& a, const t_tuple& b) const {
  return (ramBitCast<RamSigned>(a[0]) < ramBitCast<RamSigned>(b[0])) ? -1 : (ramBitCast<RamSigned>(a[0]) > ramBitCast<RamSigned>(b[0])) ? 1 :((ramBitCast<RamSigned>(a[1]) < ramBitCast<RamSigned>(b[1])) ? -1 : (ramBitCast<RamSigned>(a[1]) > ramBitCast<RamSigned>(b[1])) ? 1 :(0));
 }
bool less(const t_tuple& a, const t_tuple& b) const {
  return (ramBitCast<RamSigned>(a[0]) < ramBitCast<RamSigned>(b[0]))|| ((ramBitCast<RamSigned>(a[0]) == ramBitCast<RamSigned>(b[0])) && ((ramBitCast<RamSigned>(a[1]) < ramBitCast<RamSigned>(b[1]))));
 }
bool equal(const t_tuple& a, const t_tuple& b) const {
return (ramBitCast<RamSigned>(a[0]) == ramBitCast<RamSigned>(b[0]))&&(ramBitCast<RamSigned>(a[1]) == ramBitCast<RamSigned>(b[1]));
 }
};
using t_ind_0 = btree_set<t_tuple,t_comparator_0>;
t_ind_0 ind_0;
using iterator = t_ind_0::iterator;
struct context {
t_ind_0::operation_hints hints_0_lower;
t_ind_0::operation_hints hints_0_upper;
};
context createContext() { return context(); }
bool insert(const t_tuple& t);
bool insert(const t_tuple& t, context& h);
bool insert(const RamDomain* ramDomain);
bool insert(RamDomain a0,RamDomain a1);
bool contains(const t_tuple& t, context& h) const;
bool contains(const t_tuple& t) const;
std::size_t size() const;
iterator find(const t_tuple& t, context& h) const;
iterator find(const t_tuple& t) const;
range<iterator> lowerUpperRange_00(const t_tuple& /* lower */, const t_tuple& /* upper */, context& /* h */) const;
range<iterator> lowerUpperRange_00(const t_tuple& /* lower */, const t_tuple& /* upper */) const;
range<t_ind_0::iterator> lowerUpperRange_11(const t_tuple& lower, const t_tuple& upper, context& h) const;
range<t_ind_0::iterator> lowerUpperRange_11(const t_tuple& lower, const t_tuple& upper) const;
range<t_ind_0::iterator> lowerUpperRange_10(const t_tuple& lower, const t_tuple& upper, context& h) const;
range<t_ind_0::iterator> lowerUpperRange_10(const t_tuple& lower, const t_tuple& upper) const;
bool empty() const;
std::vector<range<iterator>> partition() const;
void purge();
iterator begin() const;
iterator end() const;
void printStatistics(std::ostream& o) const;
};
} // namespace souffle::t_btree_ii__0_1__11__10 
namespace souffle::t_btree_ii__0_1__11__10 {
using t_ind_0 = Type::t_ind_0;
using iterator = Type::iterator;
using context = Type::context;
bool Type::insert(const t_tuple& t) {
context h;
return insert(t, h);
}
bool Type::insert(const t_tuple& t, context& h) {
if (ind_0.insert(t, h.hints_0_lower)) {
return true;
} else return false;
}
bool Type::insert(const RamDomain* ramDomain) {
RamDomain data[2];
std::copy(ramDomain, ramDomain + 2, data);
const t_tuple& tuple = reinterpret_cast<const t_tuple&>(data);
context h;
return insert(tuple, h);
}
bool Type::insert(RamDomain a0,RamDomain a1) {
RamDomain data[2] = {a0,a1};
return insert(data);
}
bool Type::contains(const t_tuple& t, context& h) const {
return ind_0.contains(t, h.hints_0_lower);
}
bool Type::contains(const t_tuple& t) const {
context h;
return contains(t, h);
}
std::size_t Type::size() const {
return ind_0.size();
}
iterator Type::find(const t_tuple& t, context& h) const {
return ind_0.find(t, h.hints_0_lower);
}
iterator Type::find(const t_tuple& t) const {
context h;
return find(t, h);
}
range<iterator> Type::lowerUpperRange_00(const t_tuple& /* lower */, const t_tuple& /* upper */, context& /* h */) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<iterator> Type::lowerUpperRange_00(const t_tuple& /* lower */, const t_tuple& /* upper */) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<t_ind_0::iterator> Type::lowerUpperRange_11(const t_tuple& lower, const t_tuple& upper, context& h) const {
t_comparator_0 comparator;
int cmp = comparator(lower, upper);
if (cmp == 0) {
    auto pos = ind_0.find(lower, h.hints_0_lower);
    auto fin = ind_0.end();
    if (pos != fin) {fin = pos; ++fin;}
    return make_range(pos, fin);
}
if (cmp > 0) {
    return make_range(ind_0.end(), ind_0.end());
}
return make_range(ind_0.lower_bound(lower, h.hints_0_lower), ind_0.upper_bound(upper, h.hints_0_upper));
}
range<t_ind_0::iterator> Type::lowerUpperRange_11(const t_tuple& lower, const t_tuple& upper) const {
context h;
return lowerUpperRange_11(lower,upper,h);
}
range<t_ind_0::iterator> Type::lowerUpperRange_10(const t_tuple& lower, const t_tuple& upper, context& h) const {
t_comparator_0 comparator;
int cmp = comparator(lower, upper);
if (cmp > 0) {
    return make_range(ind_0.end(), ind_0.end());
}
return make_range(ind_0.lower_bound(lower, h.hints_0_lower), ind_0.upper_bound(upper, h.hints_0_upper));
}
range<t_ind_0::iterator> Type::lowerUpperRange_10(const t_tuple& lower, const t_tuple& upper) const {
context h;
return lowerUpperRange_10(lower,upper,h);
}
bool Type::empty() const {
return ind_0.empty();
}
std::vector<range<iterator>> Type::partition() const {
return ind_0.getChunks(400);
}
void Type::purge() {
ind_0.clear();
}
iterator Type::begin() const {
return ind_0.begin();
}
iterator Type::end() const {
return ind_0.end();
}
void Type::printStatistics(std::ostream& o) const {
o << " arity 2 direct b-tree index 0 lex-order [0,1]\n";
ind_0.printStats(o);
}
} // namespace souffle::t_btree_ii__0_1__11__10 
namespace souffle::t_btree_iii__0_1_2__100__110__111 {
struct Type {
static constexpr Relation::arity_type Arity = 3;
using t_tuple = Tuple<RamDomain, 3>;
struct t_comparator_0{
 int operator()(const t_tuple& a, const t_tuple& b) const {
  return (ramBitCast<RamSigned>(a[0]) < ramBitCast<RamSigned>(b[0])) ? -1 : (ramBitCast<RamSigned>(a[0]) > ramBitCast<RamSigned>(b[0])) ? 1 :((ramBitCast<RamSigned>(a[1]) < ramBitCast<RamSigned>(b[1])) ? -1 : (ramBitCast<RamSigned>(a[1]) > ramBitCast<RamSigned>(b[1])) ? 1 :((ramBitCast<RamSigned>(a[2]) < ramBitCast<RamSigned>(b[2])) ? -1 : (ramBitCast<RamSigned>(a[2]) > ramBitCast<RamSigned>(b[2])) ? 1 :(0)));
 }
bool less(const t_tuple& a, const t_tuple& b) const {
  return (ramBitCast<RamSigned>(a[0]) < ramBitCast<RamSigned>(b[0]))|| ((ramBitCast<RamSigned>(a[0]) == ramBitCast<RamSigned>(b[0])) && ((ramBitCast<RamSigned>(a[1]) < ramBitCast<RamSigned>(b[1]))|| ((ramBitCast<RamSigned>(a[1]) == ramBitCast<RamSigned>(b[1])) && ((ramBitCast<RamSigned>(a[2]) < ramBitCast<RamSigned>(b[2]))))));
 }
bool equal(const t_tuple& a, const t_tuple& b) const {
return (ramBitCast<RamSigned>(a[0]) == ramBitCast<RamSigned>(b[0]))&&(ramBitCast<RamSigned>(a[1]) == ramBitCast<RamSigned>(b[1]))&&(ramBitCast<RamSigned>(a[2]) == ramBitCast<RamSigned>(b[2]));
 }
};
using t_ind_0 = btree_set<t_tuple,t_comparator_0>;
t_ind_0 ind_0;
using iterator = t_ind_0::iterator;
struct context {
t_ind_0::operation_hints hints_0_lower;
t_ind_0::operation_hints hints_0_upper;
};
context createContext() { return context(); }
bool insert(const t_tuple& t);
bool insert(const t_tuple& t, context& h);
bool insert(const RamDomain* ramDomain);
bool insert(RamDomain a0,RamDomain a1,RamDomain a2);
bool contains(const t_tuple& t, context& h) const;
bool contains(const t_tuple& t) const;
std::size_t size() const;
iterator find(const t_tuple& t, context& h) const;
iterator find(const t_tuple& t) const;
range<iterator> lowerUpperRange_000(const t_tuple& /* lower */, const t_tuple& /* upper */, context& /* h */) const;
range<iterator> lowerUpperRange_000(const t_tuple& /* lower */, const t_tuple& /* upper */) const;
range<t_ind_0::iterator> lowerUpperRange_100(const t_tuple& lower, const t_tuple& upper, context& h) const;
range<t_ind_0::iterator> lowerUpperRange_100(const t_tuple& lower, const t_tuple& upper) const;
range<t_ind_0::iterator> lowerUpperRange_110(const t_tuple& lower, const t_tuple& upper, context& h) const;
range<t_ind_0::iterator> lowerUpperRange_110(const t_tuple& lower, const t_tuple& upper) const;
range<t_ind_0::iterator> lowerUpperRange_111(const t_tuple& lower, const t_tuple& upper, context& h) const;
range<t_ind_0::iterator> lowerUpperRange_111(const t_tuple& lower, const t_tuple& upper) const;
bool empty() const;
std::vector<range<iterator>> partition() const;
void purge();
iterator begin() const;
iterator end() const;
void printStatistics(std::ostream& o) const;
};
} // namespace souffle::t_btree_iii__0_1_2__100__110__111 
namespace souffle::t_btree_iii__0_1_2__100__110__111 {
using t_ind_0 = Type::t_ind_0;
using iterator = Type::iterator;
using context = Type::context;
bool Type::insert(const t_tuple& t) {
context h;
return insert(t, h);
}
bool Type::insert(const t_tuple& t, context& h) {
if (ind_0.insert(t, h.hints_0_lower)) {
return true;
} else return false;
}
bool Type::insert(const RamDomain* ramDomain) {
RamDomain data[3];
std::copy(ramDomain, ramDomain + 3, data);
const t_tuple& tuple = reinterpret_cast<const t_tuple&>(data);
context h;
return insert(tuple, h);
}
bool Type::insert(RamDomain a0,RamDomain a1,RamDomain a2) {
RamDomain data[3] = {a0,a1,a2};
return insert(data);
}
bool Type::contains(const t_tuple& t, context& h) const {
return ind_0.contains(t, h.hints_0_lower);
}
bool Type::contains(const t_tuple& t) const {
context h;
return contains(t, h);
}
std::size_t Type::size() const {
return ind_0.size();
}
iterator Type::find(const t_tuple& t, context& h) const {
return ind_0.find(t, h.hints_0_lower);
}
iterator Type::find(const t_tuple& t) const {
context h;
return find(t, h);
}
range<iterator> Type::lowerUpperRange_000(const t_tuple& /* lower */, const t_tuple& /* upper */, context& /* h */) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<iterator> Type::lowerUpperRange_000(const t_tuple& /* lower */, const t_tuple& /* upper */) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<t_ind_0::iterator> Type::lowerUpperRange_100(const t_tuple& lower, const t_tuple& upper, context& h) const {
t_comparator_0 comparator;
int cmp = comparator(lower, upper);
if (cmp > 0) {
    return make_range(ind_0.end(), ind_0.end());
}
return make_range(ind_0.lower_bound(lower, h.hints_0_lower), ind_0.upper_bound(upper, h.hints_0_upper));
}
range<t_ind_0::iterator> Type::lowerUpperRange_100(const t_tuple& lower, const t_tuple& upper) const {
context h;
return lowerUpperRange_100(lower,upper,h);
}
range<t_ind_0::iterator> Type::lowerUpperRange_110(const t_tuple& lower, const t_tuple& upper, context& h) const {
t_comparator_0 comparator;
int cmp = comparator(lower, upper);
if (cmp > 0) {
    return make_range(ind_0.end(), ind_0.end());
}
return make_range(ind_0.lower_bound(lower, h.hints_0_lower), ind_0.upper_bound(upper, h.hints_0_upper));
}
range<t_ind_0::iterator> Type::lowerUpperRange_110(const t_tuple& lower, const t_tuple& upper) const {
context h;
return lowerUpperRange_110(lower,upper,h);
}
range<t_ind_0::iterator> Type::lowerUpperRange_111(const t_tuple& lower, const t_tuple& upper, context& h) const {
t_comparator_0 comparator;
int cmp = comparator(lower, upper);
if (cmp == 0) {
    auto pos = ind_0.find(lower, h.hints_0_lower);
    auto fin = ind_0.end();
    if (pos != fin) {fin = pos; ++fin;}
    return make_range(pos, fin);
}
if (cmp > 0) {
    return make_range(ind_0.end(), ind_0.end());
}
return make_range(ind_0.lower_bound(lower, h.hints_0_lower), ind_0.upper_bound(upper, h.hints_0_upper));
}
range<t_ind_0::iterator> Type::lowerUpperRange_111(const t_tuple& lower, const t_tuple& upper) const {
context h;
return lowerUpperRange_111(lower,upper,h);
}
bool Type::empty() const {
return ind_0.empty();
}
std::vector<range<iterator>> Type::partition() const {
return ind_0.getChunks(400);
}
void Type::purge() {
ind_0.clear();
}
iterator Type::begin() const {
return ind_0.begin();
}
iterator Type::end() const {
return ind_0.end();
}
void Type::printStatistics(std::ostream& o) const {
o << " arity 3 direct b-tree index 0 lex-order [0,1,2]\n";
ind_0.printStats(o);
}
} // namespace souffle::t_btree_iii__0_1_2__100__110__111 
namespace souffle::t_btree_ii__0_1__11 {
struct Type {
static constexpr Relation::arity_type Arity = 2;
using t_tuple = Tuple<RamDomain, 2>;
struct t_comparator_0{
 int operator()(const t_tuple& a, const t_tuple& b) const {
  return (ramBitCast<RamSigned>(a[0]) < ramBitCast<RamSigned>(b[0])) ? -1 : (ramBitCast<RamSigned>(a[0]) > ramBitCast<RamSigned>(b[0])) ? 1 :((ramBitCast<RamSigned>(a[1]) < ramBitCast<RamSigned>(b[1])) ? -1 : (ramBitCast<RamSigned>(a[1]) > ramBitCast<RamSigned>(b[1])) ? 1 :(0));
 }
bool less(const t_tuple& a, const t_tuple& b) const {
  return (ramBitCast<RamSigned>(a[0]) < ramBitCast<RamSigned>(b[0]))|| ((ramBitCast<RamSigned>(a[0]) == ramBitCast<RamSigned>(b[0])) && ((ramBitCast<RamSigned>(a[1]) < ramBitCast<RamSigned>(b[1]))));
 }
bool equal(const t_tuple& a, const t_tuple& b) const {
return (ramBitCast<RamSigned>(a[0]) == ramBitCast<RamSigned>(b[0]))&&(ramBitCast<RamSigned>(a[1]) == ramBitCast<RamSigned>(b[1]));
 }
};
using t_ind_0 = btree_set<t_tuple,t_comparator_0>;
t_ind_0 ind_0;
using iterator = t_ind_0::iterator;
struct context {
t_ind_0::operation_hints hints_0_lower;
t_ind_0::operation_hints hints_0_upper;
};
context createContext() { return context(); }
bool insert(const t_tuple& t);
bool insert(const t_tuple& t, context& h);
bool insert(const RamDomain* ramDomain);
bool insert(RamDomain a0,RamDomain a1);
bool contains(const t_tuple& t, context& h) const;
bool contains(const t_tuple& t) const;
std::size_t size() const;
iterator find(const t_tuple& t, context& h) const;
iterator find(const t_tuple& t) const;
range<iterator> lowerUpperRange_00(const t_tuple& /* lower */, const t_tuple& /* upper */, context& /* h */) const;
range<iterator> lowerUpperRange_00(const t_tuple& /* lower */, const t_tuple& /* upper */) const;
range<t_ind_0::iterator> lowerUpperRange_11(const t_tuple& lower, const t_tuple& upper, context& h) const;
range<t_ind_0::iterator> lowerUpperRange_11(const t_tuple& lower, const t_tuple& upper) const;
bool empty() const;
std::vector<range<iterator>> partition() const;
void purge();
iterator begin() const;
iterator end() const;
void printStatistics(std::ostream& o) const;
};
} // namespace souffle::t_btree_ii__0_1__11 
namespace souffle::t_btree_ii__0_1__11 {
using t_ind_0 = Type::t_ind_0;
using iterator = Type::iterator;
using context = Type::context;
bool Type::insert(const t_tuple& t) {
context h;
return insert(t, h);
}
bool Type::insert(const t_tuple& t, context& h) {
if (ind_0.insert(t, h.hints_0_lower)) {
return true;
} else return false;
}
bool Type::insert(const RamDomain* ramDomain) {
RamDomain data[2];
std::copy(ramDomain, ramDomain + 2, data);
const t_tuple& tuple = reinterpret_cast<const t_tuple&>(data);
context h;
return insert(tuple, h);
}
bool Type::insert(RamDomain a0,RamDomain a1) {
RamDomain data[2] = {a0,a1};
return insert(data);
}
bool Type::contains(const t_tuple& t, context& h) const {
return ind_0.contains(t, h.hints_0_lower);
}
bool Type::contains(const t_tuple& t) const {
context h;
return contains(t, h);
}
std::size_t Type::size() const {
return ind_0.size();
}
iterator Type::find(const t_tuple& t, context& h) const {
return ind_0.find(t, h.hints_0_lower);
}
iterator Type::find(const t_tuple& t) const {
context h;
return find(t, h);
}
range<iterator> Type::lowerUpperRange_00(const t_tuple& /* lower */, const t_tuple& /* upper */, context& /* h */) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<iterator> Type::lowerUpperRange_00(const t_tuple& /* lower */, const t_tuple& /* upper */) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<t_ind_0::iterator> Type::lowerUpperRange_11(const t_tuple& lower, const t_tuple& upper, context& h) const {
t_comparator_0 comparator;
int cmp = comparator(lower, upper);
if (cmp == 0) {
    auto pos = ind_0.find(lower, h.hints_0_lower);
    auto fin = ind_0.end();
    if (pos != fin) {fin = pos; ++fin;}
    return make_range(pos, fin);
}
if (cmp > 0) {
    return make_range(ind_0.end(), ind_0.end());
}
return make_range(ind_0.lower_bound(lower, h.hints_0_lower), ind_0.upper_bound(upper, h.hints_0_upper));
}
range<t_ind_0::iterator> Type::lowerUpperRange_11(const t_tuple& lower, const t_tuple& upper) const {
context h;
return lowerUpperRange_11(lower,upper,h);
}
bool Type::empty() const {
return ind_0.empty();
}
std::vector<range<iterator>> Type::partition() const {
return ind_0.getChunks(400);
}
void Type::purge() {
ind_0.clear();
}
iterator Type::begin() const {
return ind_0.begin();
}
iterator Type::end() const {
return ind_0.end();
}
void Type::printStatistics(std::ostream& o) const {
o << " arity 2 direct b-tree index 0 lex-order [0,1]\n";
ind_0.printStats(o);
}
} // namespace souffle::t_btree_ii__0_1__11 
namespace souffle::t_btree_i__0__1 {
struct Type {
static constexpr Relation::arity_type Arity = 1;
using t_tuple = Tuple<RamDomain, 1>;
struct t_comparator_0{
 int operator()(const t_tuple& a, const t_tuple& b) const {
  return (ramBitCast<RamSigned>(a[0]) < ramBitCast<RamSigned>(b[0])) ? -1 : (ramBitCast<RamSigned>(a[0]) > ramBitCast<RamSigned>(b[0])) ? 1 :(0);
 }
bool less(const t_tuple& a, const t_tuple& b) const {
  return (ramBitCast<RamSigned>(a[0]) < ramBitCast<RamSigned>(b[0]));
 }
bool equal(const t_tuple& a, const t_tuple& b) const {
return (ramBitCast<RamSigned>(a[0]) == ramBitCast<RamSigned>(b[0]));
 }
};
using t_ind_0 = btree_set<t_tuple,t_comparator_0>;
t_ind_0 ind_0;
using iterator = t_ind_0::iterator;
struct context {
t_ind_0::operation_hints hints_0_lower;
t_ind_0::operation_hints hints_0_upper;
};
context createContext() { return context(); }
bool insert(const t_tuple& t);
bool insert(const t_tuple& t, context& h);
bool insert(const RamDomain* ramDomain);
bool insert(RamDomain a0);
bool contains(const t_tuple& t, context& h) const;
bool contains(const t_tuple& t) const;
std::size_t size() const;
iterator find(const t_tuple& t, context& h) const;
iterator find(const t_tuple& t) const;
range<iterator> lowerUpperRange_0(const t_tuple& /* lower */, const t_tuple& /* upper */, context& /* h */) const;
range<iterator> lowerUpperRange_0(const t_tuple& /* lower */, const t_tuple& /* upper */) const;
range<t_ind_0::iterator> lowerUpperRange_1(const t_tuple& lower, const t_tuple& upper, context& h) const;
range<t_ind_0::iterator> lowerUpperRange_1(const t_tuple& lower, const t_tuple& upper) const;
bool empty() const;
std::vector<range<iterator>> partition() const;
void purge();
iterator begin() const;
iterator end() const;
void printStatistics(std::ostream& o) const;
};
} // namespace souffle::t_btree_i__0__1 
namespace souffle::t_btree_i__0__1 {
using t_ind_0 = Type::t_ind_0;
using iterator = Type::iterator;
using context = Type::context;
bool Type::insert(const t_tuple& t) {
context h;
return insert(t, h);
}
bool Type::insert(const t_tuple& t, context& h) {
if (ind_0.insert(t, h.hints_0_lower)) {
return true;
} else return false;
}
bool Type::insert(const RamDomain* ramDomain) {
RamDomain data[1];
std::copy(ramDomain, ramDomain + 1, data);
const t_tuple& tuple = reinterpret_cast<const t_tuple&>(data);
context h;
return insert(tuple, h);
}
bool Type::insert(RamDomain a0) {
RamDomain data[1] = {a0};
return insert(data);
}
bool Type::contains(const t_tuple& t, context& h) const {
return ind_0.contains(t, h.hints_0_lower);
}
bool Type::contains(const t_tuple& t) const {
context h;
return contains(t, h);
}
std::size_t Type::size() const {
return ind_0.size();
}
iterator Type::find(const t_tuple& t, context& h) const {
return ind_0.find(t, h.hints_0_lower);
}
iterator Type::find(const t_tuple& t) const {
context h;
return find(t, h);
}
range<iterator> Type::lowerUpperRange_0(const t_tuple& /* lower */, const t_tuple& /* upper */, context& /* h */) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<iterator> Type::lowerUpperRange_0(const t_tuple& /* lower */, const t_tuple& /* upper */) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<t_ind_0::iterator> Type::lowerUpperRange_1(const t_tuple& lower, const t_tuple& upper, context& h) const {
t_comparator_0 comparator;
int cmp = comparator(lower, upper);
if (cmp == 0) {
    auto pos = ind_0.find(lower, h.hints_0_lower);
    auto fin = ind_0.end();
    if (pos != fin) {fin = pos; ++fin;}
    return make_range(pos, fin);
}
if (cmp > 0) {
    return make_range(ind_0.end(), ind_0.end());
}
return make_range(ind_0.lower_bound(lower, h.hints_0_lower), ind_0.upper_bound(upper, h.hints_0_upper));
}
range<t_ind_0::iterator> Type::lowerUpperRange_1(const t_tuple& lower, const t_tuple& upper) const {
context h;
return lowerUpperRange_1(lower,upper,h);
}
bool Type::empty() const {
return ind_0.empty();
}
std::vector<range<iterator>> Type::partition() const {
return ind_0.getChunks(400);
}
void Type::purge() {
ind_0.clear();
}
iterator Type::begin() const {
return ind_0.begin();
}
iterator Type::end() const {
return ind_0.end();
}
void Type::printStatistics(std::ostream& o) const {
o << " arity 1 direct b-tree index 0 lex-order [0]\n";
ind_0.printStats(o);
}
} // namespace souffle::t_btree_i__0__1 
namespace souffle {
class Stratum_N_2fa3d15dc185d227 {
public:
 Stratum_N_2fa3d15dc185d227(SymbolTable& symTable,RecordTable& recordTable,bool& pruneImdtRels,bool& performIO,SignalHandler*& signalHandler,std::atomic<std::size_t>& iter,std::atomic<RamDomain>& ctr,std::string& inputDirectory,std::string& outputDirectory,t_btree_i__0__2__1::Type& rel_N_913bf6e156bb077c);
void run([[maybe_unused]] const std::vector<RamDomain>& args,[[maybe_unused]] std::vector<RamDomain>& ret);
private:
SymbolTable& symTable;
RecordTable& recordTable;
bool& pruneImdtRels;
bool& performIO;
SignalHandler*& signalHandler;
std::atomic<std::size_t>& iter;
std::atomic<RamDomain>& ctr;
std::string& inputDirectory;
std::string& outputDirectory;
t_btree_i__0__2__1::Type* rel_N_913bf6e156bb077c;
};
} // namespace souffle
namespace souffle {
 Stratum_N_2fa3d15dc185d227::Stratum_N_2fa3d15dc185d227(SymbolTable& symTable,RecordTable& recordTable,bool& pruneImdtRels,bool& performIO,SignalHandler*& signalHandler,std::atomic<std::size_t>& iter,std::atomic<RamDomain>& ctr,std::string& inputDirectory,std::string& outputDirectory,t_btree_i__0__2__1::Type& rel_N_913bf6e156bb077c):
symTable(symTable),
recordTable(recordTable),
pruneImdtRels(pruneImdtRels),
performIO(performIO),
signalHandler(signalHandler),
iter(iter),
ctr(ctr),
inputDirectory(inputDirectory),
outputDirectory(outputDirectory),
rel_N_913bf6e156bb077c(&rel_N_913bf6e156bb077c){
}

void Stratum_N_2fa3d15dc185d227::run([[maybe_unused]] const std::vector<RamDomain>& args,[[maybe_unused]] std::vector<RamDomain>& ret){
if (performIO) {
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","n"},{"auxArity","0"},{"fact-dir","."},{"filename","N.in"},{"name","N"},{"operation","input"},{"params","{\"records\": {}, \"relation\": {\"arity\": 1, \"params\": [\"n\"]}}"},{"types","{\"ADTs\": {\"+:Id\": {\"arity\": 2, \"branches\": [{\"name\": \"Add\", \"types\": [\"+:Id\", \"+:Id\"]}, {\"name\": \"Var\", \"types\": [\"i:number\"]}], \"enum\": false}}, \"records\": {}, \"relation\": {\"arity\": 1, \"types\": [\"i:number\"]}}"}});
if (!inputDirectory.empty()) {directiveMap["fact-dir"] = inputDirectory;}
IOSystem::getInstance().getReader(directiveMap, symTable, recordTable)->readAll(*rel_N_913bf6e156bb077c);
} catch (std::exception& e) {std::cerr << "Error loading N data: " << e.what() << '\n';}
}
}

} // namespace souffle

namespace souffle {
class Stratum_add_ed981d530a6b23bd {
public:
 Stratum_add_ed981d530a6b23bd(SymbolTable& symTable,RecordTable& recordTable,bool& pruneImdtRels,bool& performIO,SignalHandler*& signalHandler,std::atomic<std::size_t>& iter,std::atomic<RamDomain>& ctr,std::string& inputDirectory,std::string& outputDirectory,t_btree_iii__0_1_2__100__110__111::Type& rel_delta_add_241d705dc2fb23df,t_eqrel& rel_delta_eql_fdc75db4daac3372,t_btree_iii__0_1_2__100__110__111::Type& rel_new_add_954a8c50e586f068,t_eqrel& rel_new_eql_10ebb01129546352,t_btree_iii__0_1_2__100__110__111::Type& rel_add_48c57da858454f79,t_btree_iii__0_1_2__111::Type& rel_add_prep_e8dfec160429ed9e,t_eqrel& rel_eql_e1be027843ac9bc5,t_btree_ii__0_1__11__10::Type& rel_var_09870be8e1a4a08e);
void run([[maybe_unused]] const std::vector<RamDomain>& args,[[maybe_unused]] std::vector<RamDomain>& ret);
private:
SymbolTable& symTable;
RecordTable& recordTable;
bool& pruneImdtRels;
bool& performIO;
SignalHandler*& signalHandler;
std::atomic<std::size_t>& iter;
std::atomic<RamDomain>& ctr;
std::string& inputDirectory;
std::string& outputDirectory;
t_btree_iii__0_1_2__100__110__111::Type* rel_delta_add_241d705dc2fb23df;
t_eqrel* rel_delta_eql_fdc75db4daac3372;
t_btree_iii__0_1_2__100__110__111::Type* rel_new_add_954a8c50e586f068;
t_eqrel* rel_new_eql_10ebb01129546352;
t_btree_iii__0_1_2__100__110__111::Type* rel_add_48c57da858454f79;
t_btree_iii__0_1_2__111::Type* rel_add_prep_e8dfec160429ed9e;
t_eqrel* rel_eql_e1be027843ac9bc5;
t_btree_ii__0_1__11__10::Type* rel_var_09870be8e1a4a08e;
};
} // namespace souffle
namespace souffle {
 Stratum_add_ed981d530a6b23bd::Stratum_add_ed981d530a6b23bd(SymbolTable& symTable,RecordTable& recordTable,bool& pruneImdtRels,bool& performIO,SignalHandler*& signalHandler,std::atomic<std::size_t>& iter,std::atomic<RamDomain>& ctr,std::string& inputDirectory,std::string& outputDirectory,t_btree_iii__0_1_2__100__110__111::Type& rel_delta_add_241d705dc2fb23df,t_eqrel& rel_delta_eql_fdc75db4daac3372,t_btree_iii__0_1_2__100__110__111::Type& rel_new_add_954a8c50e586f068,t_eqrel& rel_new_eql_10ebb01129546352,t_btree_iii__0_1_2__100__110__111::Type& rel_add_48c57da858454f79,t_btree_iii__0_1_2__111::Type& rel_add_prep_e8dfec160429ed9e,t_eqrel& rel_eql_e1be027843ac9bc5,t_btree_ii__0_1__11__10::Type& rel_var_09870be8e1a4a08e):
symTable(symTable),
recordTable(recordTable),
pruneImdtRels(pruneImdtRels),
performIO(performIO),
signalHandler(signalHandler),
iter(iter),
ctr(ctr),
inputDirectory(inputDirectory),
outputDirectory(outputDirectory),
rel_delta_add_241d705dc2fb23df(&rel_delta_add_241d705dc2fb23df),
rel_delta_eql_fdc75db4daac3372(&rel_delta_eql_fdc75db4daac3372),
rel_new_add_954a8c50e586f068(&rel_new_add_954a8c50e586f068),
rel_new_eql_10ebb01129546352(&rel_new_eql_10ebb01129546352),
rel_add_48c57da858454f79(&rel_add_48c57da858454f79),
rel_add_prep_e8dfec160429ed9e(&rel_add_prep_e8dfec160429ed9e),
rel_eql_e1be027843ac9bc5(&rel_eql_e1be027843ac9bc5),
rel_var_09870be8e1a4a08e(&rel_var_09870be8e1a4a08e){
}

void Stratum_add_ed981d530a6b23bd::run([[maybe_unused]] const std::vector<RamDomain>& args,[[maybe_unused]] std::vector<RamDomain>& ret){
signalHandler->setMsg(R"_(add(x,y,c) :- 
   add_prep(x,y,c).
in file naive.dl [21:1-21:35])_");
if(!(rel_add_prep_e8dfec160429ed9e->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt,rel_add_48c57da858454f79->createContext());
CREATE_OP_CONTEXT(rel_add_prep_e8dfec160429ed9e_op_ctxt,rel_add_prep_e8dfec160429ed9e->createContext());
for(const auto& env0 : *rel_add_prep_e8dfec160429ed9e) {
Tuple<RamDomain,3> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1]),ramBitCast(env0[2])}};
rel_add_48c57da858454f79->insert(tuple,READ_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt));
}
}
();}
signalHandler->setMsg(R"_(eql(x,x) :- 
   var(_,x).
in file naive.dl [26:1-26:24])_");
if(!(rel_var_09870be8e1a4a08e->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_eql_e1be027843ac9bc5_op_ctxt,rel_eql_e1be027843ac9bc5->createContext());
CREATE_OP_CONTEXT(rel_var_09870be8e1a4a08e_op_ctxt,rel_var_09870be8e1a4a08e->createContext());
for(const auto& env0 : *rel_var_09870be8e1a4a08e) {
Tuple<RamDomain,2> tuple{{ramBitCast(env0[1]),ramBitCast(env0[1])}};
rel_eql_e1be027843ac9bc5->insert(tuple,READ_OP_CONTEXT(rel_eql_e1be027843ac9bc5_op_ctxt));
}
}
();}
signalHandler->setMsg(R"_(eql(c1,c2) :- 
   var(x,c1),
   var(x,c2).
in file naive.dl [31:1-31:39])_");
if(!(rel_var_09870be8e1a4a08e->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_eql_e1be027843ac9bc5_op_ctxt,rel_eql_e1be027843ac9bc5->createContext());
CREATE_OP_CONTEXT(rel_var_09870be8e1a4a08e_op_ctxt,rel_var_09870be8e1a4a08e->createContext());
for(const auto& env0 : *rel_var_09870be8e1a4a08e) {
auto range = rel_var_09870be8e1a4a08e->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_var_09870be8e1a4a08e_op_ctxt));
for(const auto& env1 : range) {
Tuple<RamDomain,2> tuple{{ramBitCast(env0[1]),ramBitCast(env1[1])}};
rel_eql_e1be027843ac9bc5->insert(tuple,READ_OP_CONTEXT(rel_eql_e1be027843ac9bc5_op_ctxt));
}
}
}
();}
[&](){
CREATE_OP_CONTEXT(rel_delta_add_241d705dc2fb23df_op_ctxt,rel_delta_add_241d705dc2fb23df->createContext());
CREATE_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt,rel_add_48c57da858454f79->createContext());
for(const auto& env0 : *rel_add_48c57da858454f79) {
Tuple<RamDomain,3> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1]),ramBitCast(env0[2])}};
rel_delta_add_241d705dc2fb23df->insert(tuple,READ_OP_CONTEXT(rel_delta_add_241d705dc2fb23df_op_ctxt));
}
}
();rel_eql_e1be027843ac9bc5->extendAndInsert(*rel_delta_eql_fdc75db4daac3372);
iter = 0;
for(;;) {
signalHandler->setMsg(R"_(add(x1,y,c) :- 
   add(x,y,c),
   eql(x,x1).
in file naive.dl [34:1-34:43])_");
if(!(rel_delta_add_241d705dc2fb23df->empty()) && !(rel_eql_e1be027843ac9bc5->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_delta_add_241d705dc2fb23df_op_ctxt,rel_delta_add_241d705dc2fb23df->createContext());
CREATE_OP_CONTEXT(rel_delta_eql_fdc75db4daac3372_op_ctxt,rel_delta_eql_fdc75db4daac3372->createContext());
CREATE_OP_CONTEXT(rel_new_add_954a8c50e586f068_op_ctxt,rel_new_add_954a8c50e586f068->createContext());
CREATE_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt,rel_add_48c57da858454f79->createContext());
CREATE_OP_CONTEXT(rel_eql_e1be027843ac9bc5_op_ctxt,rel_eql_e1be027843ac9bc5->createContext());
for(const auto& env0 : *rel_delta_add_241d705dc2fb23df) {
auto range = rel_eql_e1be027843ac9bc5->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_eql_e1be027843ac9bc5_op_ctxt));
for(const auto& env1 : range) {
if( !(rel_delta_eql_fdc75db4daac3372->contains(Tuple<RamDomain,2>{{ramBitCast(env0[0]),ramBitCast(env1[1])}},READ_OP_CONTEXT(rel_delta_eql_fdc75db4daac3372_op_ctxt))) && !(rel_add_48c57da858454f79->contains(Tuple<RamDomain,3>{{ramBitCast(env1[1]),ramBitCast(env0[1]),ramBitCast(env0[2])}},READ_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt)))) {
Tuple<RamDomain,3> tuple{{ramBitCast(env1[1]),ramBitCast(env0[1]),ramBitCast(env0[2])}};
rel_new_add_954a8c50e586f068->insert(tuple,READ_OP_CONTEXT(rel_new_add_954a8c50e586f068_op_ctxt));
}
}
}
}
();}
signalHandler->setMsg(R"_(add(x1,y,c) :- 
   add(x,y,c),
   eql(x,x1).
in file naive.dl [34:1-34:43])_");
if(!(rel_add_48c57da858454f79->empty()) && !(rel_delta_eql_fdc75db4daac3372->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_delta_eql_fdc75db4daac3372_op_ctxt,rel_delta_eql_fdc75db4daac3372->createContext());
CREATE_OP_CONTEXT(rel_new_add_954a8c50e586f068_op_ctxt,rel_new_add_954a8c50e586f068->createContext());
CREATE_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt,rel_add_48c57da858454f79->createContext());
for(const auto& env0 : *rel_add_48c57da858454f79) {
auto range = rel_delta_eql_fdc75db4daac3372->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_delta_eql_fdc75db4daac3372_op_ctxt));
for(const auto& env1 : range) {
if( !(rel_add_48c57da858454f79->contains(Tuple<RamDomain,3>{{ramBitCast(env1[1]),ramBitCast(env0[1]),ramBitCast(env0[2])}},READ_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt)))) {
Tuple<RamDomain,3> tuple{{ramBitCast(env1[1]),ramBitCast(env0[1]),ramBitCast(env0[2])}};
rel_new_add_954a8c50e586f068->insert(tuple,READ_OP_CONTEXT(rel_new_add_954a8c50e586f068_op_ctxt));
}
}
}
}
();}
signalHandler->setMsg(R"_(add(x,y1,c) :- 
   add(x,y,c),
   eql(y,y1).
in file naive.dl [35:1-35:43])_");
if(!(rel_delta_add_241d705dc2fb23df->empty()) && !(rel_eql_e1be027843ac9bc5->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_delta_add_241d705dc2fb23df_op_ctxt,rel_delta_add_241d705dc2fb23df->createContext());
CREATE_OP_CONTEXT(rel_delta_eql_fdc75db4daac3372_op_ctxt,rel_delta_eql_fdc75db4daac3372->createContext());
CREATE_OP_CONTEXT(rel_new_add_954a8c50e586f068_op_ctxt,rel_new_add_954a8c50e586f068->createContext());
CREATE_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt,rel_add_48c57da858454f79->createContext());
CREATE_OP_CONTEXT(rel_eql_e1be027843ac9bc5_op_ctxt,rel_eql_e1be027843ac9bc5->createContext());
for(const auto& env0 : *rel_delta_add_241d705dc2fb23df) {
auto range = rel_eql_e1be027843ac9bc5->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_eql_e1be027843ac9bc5_op_ctxt));
for(const auto& env1 : range) {
if( !(rel_delta_eql_fdc75db4daac3372->contains(Tuple<RamDomain,2>{{ramBitCast(env0[1]),ramBitCast(env1[1])}},READ_OP_CONTEXT(rel_delta_eql_fdc75db4daac3372_op_ctxt))) && !(rel_add_48c57da858454f79->contains(Tuple<RamDomain,3>{{ramBitCast(env0[0]),ramBitCast(env1[1]),ramBitCast(env0[2])}},READ_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt)))) {
Tuple<RamDomain,3> tuple{{ramBitCast(env0[0]),ramBitCast(env1[1]),ramBitCast(env0[2])}};
rel_new_add_954a8c50e586f068->insert(tuple,READ_OP_CONTEXT(rel_new_add_954a8c50e586f068_op_ctxt));
}
}
}
}
();}
signalHandler->setMsg(R"_(add(x,y1,c) :- 
   add(x,y,c),
   eql(y,y1).
in file naive.dl [35:1-35:43])_");
if(!(rel_add_48c57da858454f79->empty()) && !(rel_delta_eql_fdc75db4daac3372->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_delta_eql_fdc75db4daac3372_op_ctxt,rel_delta_eql_fdc75db4daac3372->createContext());
CREATE_OP_CONTEXT(rel_new_add_954a8c50e586f068_op_ctxt,rel_new_add_954a8c50e586f068->createContext());
CREATE_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt,rel_add_48c57da858454f79->createContext());
for(const auto& env0 : *rel_add_48c57da858454f79) {
auto range = rel_delta_eql_fdc75db4daac3372->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_delta_eql_fdc75db4daac3372_op_ctxt));
for(const auto& env1 : range) {
if( !(rel_add_48c57da858454f79->contains(Tuple<RamDomain,3>{{ramBitCast(env0[0]),ramBitCast(env1[1]),ramBitCast(env0[2])}},READ_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt)))) {
Tuple<RamDomain,3> tuple{{ramBitCast(env0[0]),ramBitCast(env1[1]),ramBitCast(env0[2])}};
rel_new_add_954a8c50e586f068->insert(tuple,READ_OP_CONTEXT(rel_new_add_954a8c50e586f068_op_ctxt));
}
}
}
}
();}
signalHandler->setMsg(R"_(add(x,y,c1) :- 
   add(x,y,c),
   eql(c,c1).
in file naive.dl [36:1-36:43])_");
if(!(rel_delta_add_241d705dc2fb23df->empty()) && !(rel_eql_e1be027843ac9bc5->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_delta_add_241d705dc2fb23df_op_ctxt,rel_delta_add_241d705dc2fb23df->createContext());
CREATE_OP_CONTEXT(rel_delta_eql_fdc75db4daac3372_op_ctxt,rel_delta_eql_fdc75db4daac3372->createContext());
CREATE_OP_CONTEXT(rel_new_add_954a8c50e586f068_op_ctxt,rel_new_add_954a8c50e586f068->createContext());
CREATE_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt,rel_add_48c57da858454f79->createContext());
CREATE_OP_CONTEXT(rel_eql_e1be027843ac9bc5_op_ctxt,rel_eql_e1be027843ac9bc5->createContext());
for(const auto& env0 : *rel_delta_add_241d705dc2fb23df) {
auto range = rel_eql_e1be027843ac9bc5->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[2]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[2]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_eql_e1be027843ac9bc5_op_ctxt));
for(const auto& env1 : range) {
if( !(rel_delta_eql_fdc75db4daac3372->contains(Tuple<RamDomain,2>{{ramBitCast(env0[2]),ramBitCast(env1[1])}},READ_OP_CONTEXT(rel_delta_eql_fdc75db4daac3372_op_ctxt))) && !(rel_add_48c57da858454f79->contains(Tuple<RamDomain,3>{{ramBitCast(env0[0]),ramBitCast(env0[1]),ramBitCast(env1[1])}},READ_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt)))) {
Tuple<RamDomain,3> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1]),ramBitCast(env1[1])}};
rel_new_add_954a8c50e586f068->insert(tuple,READ_OP_CONTEXT(rel_new_add_954a8c50e586f068_op_ctxt));
}
}
}
}
();}
signalHandler->setMsg(R"_(add(x,y,c1) :- 
   add(x,y,c),
   eql(c,c1).
in file naive.dl [36:1-36:43])_");
if(!(rel_add_48c57da858454f79->empty()) && !(rel_delta_eql_fdc75db4daac3372->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_delta_eql_fdc75db4daac3372_op_ctxt,rel_delta_eql_fdc75db4daac3372->createContext());
CREATE_OP_CONTEXT(rel_new_add_954a8c50e586f068_op_ctxt,rel_new_add_954a8c50e586f068->createContext());
CREATE_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt,rel_add_48c57da858454f79->createContext());
for(const auto& env0 : *rel_add_48c57da858454f79) {
auto range = rel_delta_eql_fdc75db4daac3372->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[2]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[2]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_delta_eql_fdc75db4daac3372_op_ctxt));
for(const auto& env1 : range) {
if( !(rel_add_48c57da858454f79->contains(Tuple<RamDomain,3>{{ramBitCast(env0[0]),ramBitCast(env0[1]),ramBitCast(env1[1])}},READ_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt)))) {
Tuple<RamDomain,3> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1]),ramBitCast(env1[1])}};
rel_new_add_954a8c50e586f068->insert(tuple,READ_OP_CONTEXT(rel_new_add_954a8c50e586f068_op_ctxt));
}
}
}
}
();}
signalHandler->setMsg(R"_(add(x,y,$Add(x, y)) :- 
   add(y,x,_).
in file naive.dl [39:1-43:18])_");
if(!(rel_delta_add_241d705dc2fb23df->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_delta_add_241d705dc2fb23df_op_ctxt,rel_delta_add_241d705dc2fb23df->createContext());
CREATE_OP_CONTEXT(rel_new_add_954a8c50e586f068_op_ctxt,rel_new_add_954a8c50e586f068->createContext());
CREATE_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt,rel_add_48c57da858454f79->createContext());
for(const auto& env0 : *rel_delta_add_241d705dc2fb23df) {
if( !(rel_add_48c57da858454f79->contains(Tuple<RamDomain,3>{{ramBitCast(env0[1]),ramBitCast(env0[0]),ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(RamSigned(0))),ramBitCast(ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(env0[1])),ramBitCast(ramBitCast(env0[0]))}}
)))}}
))}},READ_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt)))) {
Tuple<RamDomain,3> tuple{{ramBitCast(env0[1]),ramBitCast(env0[0]),ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(RamSigned(0))),ramBitCast(ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(env0[1])),ramBitCast(ramBitCast(env0[0]))}}
)))}}
))}};
rel_new_add_954a8c50e586f068->insert(tuple,READ_OP_CONTEXT(rel_new_add_954a8c50e586f068_op_ctxt));
}
}
}
();}
signalHandler->setMsg(R"_(add(x,$Add(y, z),$Add(x, $Add(y, z))) :- 
   add(x,y,xy),
   add(xy,z,_).
in file naive.dl [46:1-51:38])_");
if(!(rel_delta_add_241d705dc2fb23df->empty()) && !(rel_add_48c57da858454f79->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_delta_add_241d705dc2fb23df_op_ctxt,rel_delta_add_241d705dc2fb23df->createContext());
CREATE_OP_CONTEXT(rel_new_add_954a8c50e586f068_op_ctxt,rel_new_add_954a8c50e586f068->createContext());
CREATE_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt,rel_add_48c57da858454f79->createContext());
for(const auto& env0 : *rel_delta_add_241d705dc2fb23df) {
auto range = rel_add_48c57da858454f79->lowerUpperRange_100(Tuple<RamDomain,3>{{ramBitCast(env0[2]), ramBitCast<RamDomain>(MIN_RAM_SIGNED), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,3>{{ramBitCast(env0[2]), ramBitCast<RamDomain>(MAX_RAM_SIGNED), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt));
for(const auto& env1 : range) {
if( !(!rel_delta_add_241d705dc2fb23df->lowerUpperRange_110(Tuple<RamDomain,3>{{ramBitCast(env0[2]), ramBitCast(env1[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,3>{{ramBitCast(env0[2]), ramBitCast(env1[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_delta_add_241d705dc2fb23df_op_ctxt)).empty()) && !(rel_add_48c57da858454f79->contains(Tuple<RamDomain,3>{{ramBitCast(env0[0]),ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(RamSigned(0))),ramBitCast(ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(env0[1])),ramBitCast(ramBitCast(env1[1]))}}
)))}}
)),ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(RamSigned(0))),ramBitCast(ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(env0[0])),ramBitCast(ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(RamSigned(0))),ramBitCast(ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(env0[1])),ramBitCast(ramBitCast(env1[1]))}}
)))}}
)))}}
)))}}
))}},READ_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt)))) {
Tuple<RamDomain,3> tuple{{ramBitCast(env0[0]),ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(RamSigned(0))),ramBitCast(ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(env0[1])),ramBitCast(ramBitCast(env1[1]))}}
)))}}
)),ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(RamSigned(0))),ramBitCast(ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(env0[0])),ramBitCast(ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(RamSigned(0))),ramBitCast(ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(env0[1])),ramBitCast(ramBitCast(env1[1]))}}
)))}}
)))}}
)))}}
))}};
rel_new_add_954a8c50e586f068->insert(tuple,READ_OP_CONTEXT(rel_new_add_954a8c50e586f068_op_ctxt));
}
}
}
}
();}
signalHandler->setMsg(R"_(add(x,$Add(y, z),$Add(x, $Add(y, z))) :- 
   add(x,y,xy),
   add(xy,z,_).
in file naive.dl [46:1-51:38])_");
if(!(rel_add_48c57da858454f79->empty()) && !(rel_delta_add_241d705dc2fb23df->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_delta_add_241d705dc2fb23df_op_ctxt,rel_delta_add_241d705dc2fb23df->createContext());
CREATE_OP_CONTEXT(rel_new_add_954a8c50e586f068_op_ctxt,rel_new_add_954a8c50e586f068->createContext());
CREATE_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt,rel_add_48c57da858454f79->createContext());
for(const auto& env0 : *rel_add_48c57da858454f79) {
auto range = rel_delta_add_241d705dc2fb23df->lowerUpperRange_100(Tuple<RamDomain,3>{{ramBitCast(env0[2]), ramBitCast<RamDomain>(MIN_RAM_SIGNED), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,3>{{ramBitCast(env0[2]), ramBitCast<RamDomain>(MAX_RAM_SIGNED), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_delta_add_241d705dc2fb23df_op_ctxt));
for(const auto& env1 : range) {
if( !(rel_add_48c57da858454f79->contains(Tuple<RamDomain,3>{{ramBitCast(env0[0]),ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(RamSigned(0))),ramBitCast(ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(env0[1])),ramBitCast(ramBitCast(env1[1]))}}
)))}}
)),ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(RamSigned(0))),ramBitCast(ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(env0[0])),ramBitCast(ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(RamSigned(0))),ramBitCast(ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(env0[1])),ramBitCast(ramBitCast(env1[1]))}}
)))}}
)))}}
)))}}
))}},READ_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt)))) {
Tuple<RamDomain,3> tuple{{ramBitCast(env0[0]),ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(RamSigned(0))),ramBitCast(ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(env0[1])),ramBitCast(ramBitCast(env1[1]))}}
)))}}
)),ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(RamSigned(0))),ramBitCast(ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(env0[0])),ramBitCast(ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(RamSigned(0))),ramBitCast(ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(env0[1])),ramBitCast(ramBitCast(env1[1]))}}
)))}}
)))}}
)))}}
))}};
rel_new_add_954a8c50e586f068->insert(tuple,READ_OP_CONTEXT(rel_new_add_954a8c50e586f068_op_ctxt));
}
}
}
}
();}
signalHandler->setMsg(R"_(add(y,z,$Add(y, z)) :- 
   add(_,y,xy),
   add(xy,z,_).
in file naive.dl [46:1-51:38])_");
if(!(rel_delta_add_241d705dc2fb23df->empty()) && !(rel_add_48c57da858454f79->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_delta_add_241d705dc2fb23df_op_ctxt,rel_delta_add_241d705dc2fb23df->createContext());
CREATE_OP_CONTEXT(rel_new_add_954a8c50e586f068_op_ctxt,rel_new_add_954a8c50e586f068->createContext());
CREATE_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt,rel_add_48c57da858454f79->createContext());
for(const auto& env0 : *rel_delta_add_241d705dc2fb23df) {
auto range = rel_add_48c57da858454f79->lowerUpperRange_100(Tuple<RamDomain,3>{{ramBitCast(env0[2]), ramBitCast<RamDomain>(MIN_RAM_SIGNED), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,3>{{ramBitCast(env0[2]), ramBitCast<RamDomain>(MAX_RAM_SIGNED), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt));
for(const auto& env1 : range) {
if( !(rel_add_48c57da858454f79->contains(Tuple<RamDomain,3>{{ramBitCast(env0[1]),ramBitCast(env1[1]),ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(RamSigned(0))),ramBitCast(ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(env0[1])),ramBitCast(ramBitCast(env1[1]))}}
)))}}
))}},READ_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt))) && !(!rel_delta_add_241d705dc2fb23df->lowerUpperRange_110(Tuple<RamDomain,3>{{ramBitCast(env0[2]), ramBitCast(env1[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,3>{{ramBitCast(env0[2]), ramBitCast(env1[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_delta_add_241d705dc2fb23df_op_ctxt)).empty())) {
Tuple<RamDomain,3> tuple{{ramBitCast(env0[1]),ramBitCast(env1[1]),ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(RamSigned(0))),ramBitCast(ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(env0[1])),ramBitCast(ramBitCast(env1[1]))}}
)))}}
))}};
rel_new_add_954a8c50e586f068->insert(tuple,READ_OP_CONTEXT(rel_new_add_954a8c50e586f068_op_ctxt));
}
}
}
}
();}
signalHandler->setMsg(R"_(add(y,z,$Add(y, z)) :- 
   add(_,y,xy),
   add(xy,z,_).
in file naive.dl [46:1-51:38])_");
if(!(rel_add_48c57da858454f79->empty()) && !(rel_delta_add_241d705dc2fb23df->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_delta_add_241d705dc2fb23df_op_ctxt,rel_delta_add_241d705dc2fb23df->createContext());
CREATE_OP_CONTEXT(rel_new_add_954a8c50e586f068_op_ctxt,rel_new_add_954a8c50e586f068->createContext());
CREATE_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt,rel_add_48c57da858454f79->createContext());
for(const auto& env0 : *rel_add_48c57da858454f79) {
auto range = rel_delta_add_241d705dc2fb23df->lowerUpperRange_100(Tuple<RamDomain,3>{{ramBitCast(env0[2]), ramBitCast<RamDomain>(MIN_RAM_SIGNED), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,3>{{ramBitCast(env0[2]), ramBitCast<RamDomain>(MAX_RAM_SIGNED), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_delta_add_241d705dc2fb23df_op_ctxt));
for(const auto& env1 : range) {
if( !(rel_add_48c57da858454f79->contains(Tuple<RamDomain,3>{{ramBitCast(env0[1]),ramBitCast(env1[1]),ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(RamSigned(0))),ramBitCast(ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(env0[1])),ramBitCast(ramBitCast(env1[1]))}}
)))}}
))}},READ_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt)))) {
Tuple<RamDomain,3> tuple{{ramBitCast(env0[1]),ramBitCast(env1[1]),ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(RamSigned(0))),ramBitCast(ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(env0[1])),ramBitCast(ramBitCast(env1[1]))}}
)))}}
))}};
rel_new_add_954a8c50e586f068->insert(tuple,READ_OP_CONTEXT(rel_new_add_954a8c50e586f068_op_ctxt));
}
}
}
}
();}
signalHandler->setMsg(R"_(eql(x,x) :- 
   add(_,_,x).
in file naive.dl [27:1-27:27])_");
if(!(rel_delta_add_241d705dc2fb23df->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_delta_add_241d705dc2fb23df_op_ctxt,rel_delta_add_241d705dc2fb23df->createContext());
CREATE_OP_CONTEXT(rel_new_eql_10ebb01129546352_op_ctxt,rel_new_eql_10ebb01129546352->createContext());
CREATE_OP_CONTEXT(rel_eql_e1be027843ac9bc5_op_ctxt,rel_eql_e1be027843ac9bc5->createContext());
for(const auto& env0 : *rel_delta_add_241d705dc2fb23df) {
if( !(rel_eql_e1be027843ac9bc5->contains(Tuple<RamDomain,2>{{ramBitCast(env0[2]),ramBitCast(env0[2])}},READ_OP_CONTEXT(rel_eql_e1be027843ac9bc5_op_ctxt)))) {
Tuple<RamDomain,2> tuple{{ramBitCast(env0[2]),ramBitCast(env0[2])}};
rel_new_eql_10ebb01129546352->insert(tuple,READ_OP_CONTEXT(rel_new_eql_10ebb01129546352_op_ctxt));
}
}
}
();}
signalHandler->setMsg(R"_(eql(c1,c2) :- 
   add(x,y,c1),
   add(x,y,c2).
in file naive.dl [30:1-30:45])_");
if(!(rel_delta_add_241d705dc2fb23df->empty()) && !(rel_add_48c57da858454f79->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_delta_add_241d705dc2fb23df_op_ctxt,rel_delta_add_241d705dc2fb23df->createContext());
CREATE_OP_CONTEXT(rel_new_eql_10ebb01129546352_op_ctxt,rel_new_eql_10ebb01129546352->createContext());
CREATE_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt,rel_add_48c57da858454f79->createContext());
CREATE_OP_CONTEXT(rel_eql_e1be027843ac9bc5_op_ctxt,rel_eql_e1be027843ac9bc5->createContext());
for(const auto& env0 : *rel_delta_add_241d705dc2fb23df) {
auto range = rel_add_48c57da858454f79->lowerUpperRange_110(Tuple<RamDomain,3>{{ramBitCast(env0[0]), ramBitCast(env0[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,3>{{ramBitCast(env0[0]), ramBitCast(env0[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt));
for(const auto& env1 : range) {
if( !(rel_eql_e1be027843ac9bc5->contains(Tuple<RamDomain,2>{{ramBitCast(env0[2]),ramBitCast(env1[2])}},READ_OP_CONTEXT(rel_eql_e1be027843ac9bc5_op_ctxt))) && !(rel_delta_add_241d705dc2fb23df->contains(Tuple<RamDomain,3>{{ramBitCast(env0[0]),ramBitCast(env0[1]),ramBitCast(env1[2])}},READ_OP_CONTEXT(rel_delta_add_241d705dc2fb23df_op_ctxt)))) {
Tuple<RamDomain,2> tuple{{ramBitCast(env0[2]),ramBitCast(env1[2])}};
rel_new_eql_10ebb01129546352->insert(tuple,READ_OP_CONTEXT(rel_new_eql_10ebb01129546352_op_ctxt));
}
}
}
}
();}
signalHandler->setMsg(R"_(eql(c1,c2) :- 
   add(x,y,c1),
   add(x,y,c2).
in file naive.dl [30:1-30:45])_");
if(!(rel_add_48c57da858454f79->empty()) && !(rel_delta_add_241d705dc2fb23df->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_delta_add_241d705dc2fb23df_op_ctxt,rel_delta_add_241d705dc2fb23df->createContext());
CREATE_OP_CONTEXT(rel_new_eql_10ebb01129546352_op_ctxt,rel_new_eql_10ebb01129546352->createContext());
CREATE_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt,rel_add_48c57da858454f79->createContext());
CREATE_OP_CONTEXT(rel_eql_e1be027843ac9bc5_op_ctxt,rel_eql_e1be027843ac9bc5->createContext());
for(const auto& env0 : *rel_add_48c57da858454f79) {
auto range = rel_delta_add_241d705dc2fb23df->lowerUpperRange_110(Tuple<RamDomain,3>{{ramBitCast(env0[0]), ramBitCast(env0[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,3>{{ramBitCast(env0[0]), ramBitCast(env0[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_delta_add_241d705dc2fb23df_op_ctxt));
for(const auto& env1 : range) {
if( !(rel_eql_e1be027843ac9bc5->contains(Tuple<RamDomain,2>{{ramBitCast(env0[2]),ramBitCast(env1[2])}},READ_OP_CONTEXT(rel_eql_e1be027843ac9bc5_op_ctxt)))) {
Tuple<RamDomain,2> tuple{{ramBitCast(env0[2]),ramBitCast(env1[2])}};
rel_new_eql_10ebb01129546352->insert(tuple,READ_OP_CONTEXT(rel_new_eql_10ebb01129546352_op_ctxt));
}
}
}
}
();}
signalHandler->setMsg(R"_(eql($Add(x, y),yx) :- 
   add(y,x,yx).
in file naive.dl [39:1-43:18])_");
if(!(rel_delta_add_241d705dc2fb23df->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_delta_add_241d705dc2fb23df_op_ctxt,rel_delta_add_241d705dc2fb23df->createContext());
CREATE_OP_CONTEXT(rel_new_eql_10ebb01129546352_op_ctxt,rel_new_eql_10ebb01129546352->createContext());
CREATE_OP_CONTEXT(rel_eql_e1be027843ac9bc5_op_ctxt,rel_eql_e1be027843ac9bc5->createContext());
for(const auto& env0 : *rel_delta_add_241d705dc2fb23df) {
if( !(rel_eql_e1be027843ac9bc5->contains(Tuple<RamDomain,2>{{ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(RamSigned(0))),ramBitCast(ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(env0[1])),ramBitCast(ramBitCast(env0[0]))}}
)))}}
)),ramBitCast(env0[2])}},READ_OP_CONTEXT(rel_eql_e1be027843ac9bc5_op_ctxt)))) {
Tuple<RamDomain,2> tuple{{ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(RamSigned(0))),ramBitCast(ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(env0[1])),ramBitCast(ramBitCast(env0[0]))}}
)))}}
)),ramBitCast(env0[2])}};
rel_new_eql_10ebb01129546352->insert(tuple,READ_OP_CONTEXT(rel_new_eql_10ebb01129546352_op_ctxt));
}
}
}
();}
signalHandler->setMsg(R"_(eql(xy_z,$Add(x, $Add(y, z))) :- 
   add(x,y,xy),
   add(xy,z,xy_z).
in file naive.dl [46:1-51:38])_");
if(!(rel_delta_add_241d705dc2fb23df->empty()) && !(rel_add_48c57da858454f79->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_delta_add_241d705dc2fb23df_op_ctxt,rel_delta_add_241d705dc2fb23df->createContext());
CREATE_OP_CONTEXT(rel_new_eql_10ebb01129546352_op_ctxt,rel_new_eql_10ebb01129546352->createContext());
CREATE_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt,rel_add_48c57da858454f79->createContext());
CREATE_OP_CONTEXT(rel_eql_e1be027843ac9bc5_op_ctxt,rel_eql_e1be027843ac9bc5->createContext());
for(const auto& env0 : *rel_delta_add_241d705dc2fb23df) {
auto range = rel_add_48c57da858454f79->lowerUpperRange_100(Tuple<RamDomain,3>{{ramBitCast(env0[2]), ramBitCast<RamDomain>(MIN_RAM_SIGNED), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,3>{{ramBitCast(env0[2]), ramBitCast<RamDomain>(MAX_RAM_SIGNED), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt));
for(const auto& env1 : range) {
if( !(rel_eql_e1be027843ac9bc5->contains(Tuple<RamDomain,2>{{ramBitCast(env1[2]),ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(RamSigned(0))),ramBitCast(ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(env0[0])),ramBitCast(ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(RamSigned(0))),ramBitCast(ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(env0[1])),ramBitCast(ramBitCast(env1[1]))}}
)))}}
)))}}
)))}}
))}},READ_OP_CONTEXT(rel_eql_e1be027843ac9bc5_op_ctxt))) && !(rel_delta_add_241d705dc2fb23df->contains(Tuple<RamDomain,3>{{ramBitCast(env0[2]),ramBitCast(env1[1]),ramBitCast(env1[2])}},READ_OP_CONTEXT(rel_delta_add_241d705dc2fb23df_op_ctxt)))) {
Tuple<RamDomain,2> tuple{{ramBitCast(env1[2]),ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(RamSigned(0))),ramBitCast(ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(env0[0])),ramBitCast(ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(RamSigned(0))),ramBitCast(ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(env0[1])),ramBitCast(ramBitCast(env1[1]))}}
)))}}
)))}}
)))}}
))}};
rel_new_eql_10ebb01129546352->insert(tuple,READ_OP_CONTEXT(rel_new_eql_10ebb01129546352_op_ctxt));
}
}
}
}
();}
signalHandler->setMsg(R"_(eql(xy_z,$Add(x, $Add(y, z))) :- 
   add(x,y,xy),
   add(xy,z,xy_z).
in file naive.dl [46:1-51:38])_");
if(!(rel_add_48c57da858454f79->empty()) && !(rel_delta_add_241d705dc2fb23df->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_delta_add_241d705dc2fb23df_op_ctxt,rel_delta_add_241d705dc2fb23df->createContext());
CREATE_OP_CONTEXT(rel_new_eql_10ebb01129546352_op_ctxt,rel_new_eql_10ebb01129546352->createContext());
CREATE_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt,rel_add_48c57da858454f79->createContext());
CREATE_OP_CONTEXT(rel_eql_e1be027843ac9bc5_op_ctxt,rel_eql_e1be027843ac9bc5->createContext());
for(const auto& env0 : *rel_add_48c57da858454f79) {
auto range = rel_delta_add_241d705dc2fb23df->lowerUpperRange_100(Tuple<RamDomain,3>{{ramBitCast(env0[2]), ramBitCast<RamDomain>(MIN_RAM_SIGNED), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,3>{{ramBitCast(env0[2]), ramBitCast<RamDomain>(MAX_RAM_SIGNED), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_delta_add_241d705dc2fb23df_op_ctxt));
for(const auto& env1 : range) {
if( !(rel_eql_e1be027843ac9bc5->contains(Tuple<RamDomain,2>{{ramBitCast(env1[2]),ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(RamSigned(0))),ramBitCast(ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(env0[0])),ramBitCast(ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(RamSigned(0))),ramBitCast(ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(env0[1])),ramBitCast(ramBitCast(env1[1]))}}
)))}}
)))}}
)))}}
))}},READ_OP_CONTEXT(rel_eql_e1be027843ac9bc5_op_ctxt)))) {
Tuple<RamDomain,2> tuple{{ramBitCast(env1[2]),ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(RamSigned(0))),ramBitCast(ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(env0[0])),ramBitCast(ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(RamSigned(0))),ramBitCast(ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(env0[1])),ramBitCast(ramBitCast(env1[1]))}}
)))}}
)))}}
)))}}
))}};
rel_new_eql_10ebb01129546352->insert(tuple,READ_OP_CONTEXT(rel_new_eql_10ebb01129546352_op_ctxt));
}
}
}
}
();}
if(rel_new_add_954a8c50e586f068->empty() && rel_new_eql_10ebb01129546352->empty()) break;
[&](){
CREATE_OP_CONTEXT(rel_new_add_954a8c50e586f068_op_ctxt,rel_new_add_954a8c50e586f068->createContext());
CREATE_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt,rel_add_48c57da858454f79->createContext());
for(const auto& env0 : *rel_new_add_954a8c50e586f068) {
Tuple<RamDomain,3> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1]),ramBitCast(env0[2])}};
rel_add_48c57da858454f79->insert(tuple,READ_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt));
}
}
();std::swap(rel_delta_add_241d705dc2fb23df, rel_new_add_954a8c50e586f068);
rel_new_add_954a8c50e586f068->purge();
rel_new_eql_10ebb01129546352->extendAndInsert(*rel_eql_e1be027843ac9bc5);
std::swap(rel_delta_eql_fdc75db4daac3372, rel_new_eql_10ebb01129546352);
rel_new_eql_10ebb01129546352->purge();
iter++;
}
iter = 0;
rel_delta_add_241d705dc2fb23df->purge();
rel_new_add_954a8c50e586f068->purge();
rel_delta_eql_fdc75db4daac3372->purge();
rel_new_eql_10ebb01129546352->purge();
if (performIO) {
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","x\ty\tc"},{"auxArity","0"},{"name","add"},{"operation","output"},{"output-dir","naive"},{"params","{\"records\": {}, \"relation\": {\"arity\": 3, \"params\": [\"x\", \"y\", \"c\"]}}"},{"types","{\"ADTs\": {\"+:Id\": {\"arity\": 2, \"branches\": [{\"name\": \"Add\", \"types\": [\"+:Id\", \"+:Id\"]}, {\"name\": \"Var\", \"types\": [\"i:number\"]}], \"enum\": false}}, \"records\": {}, \"relation\": {\"arity\": 3, \"types\": [\"+:Id\", \"+:Id\", \"+:Id\"]}}"}});
if (!outputDirectory.empty()) {directiveMap["output-dir"] = outputDirectory;}
IOSystem::getInstance().getWriter(directiveMap, symTable, recordTable)->writeAll(*rel_add_48c57da858454f79);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
}
if (performIO) {
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","x\ty\tc"},{"auxArity","0"},{"name","add"},{"operation","output"},{"output-dir","naive"},{"params","{\"records\": {}, \"relation\": {\"arity\": 3, \"params\": [\"x\", \"y\", \"c\"]}}"},{"types","{\"ADTs\": {\"+:Id\": {\"arity\": 2, \"branches\": [{\"name\": \"Add\", \"types\": [\"+:Id\", \"+:Id\"]}, {\"name\": \"Var\", \"types\": [\"i:number\"]}], \"enum\": false}}, \"records\": {}, \"relation\": {\"arity\": 3, \"types\": [\"+:Id\", \"+:Id\", \"+:Id\"]}}"}});
if (!outputDirectory.empty()) {directiveMap["output-dir"] = outputDirectory;}
IOSystem::getInstance().getWriter(directiveMap, symTable, recordTable)->writeAll(*rel_add_48c57da858454f79);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
}
if (pruneImdtRels) rel_add_48c57da858454f79->purge();
if (pruneImdtRels) rel_add_prep_e8dfec160429ed9e->purge();
if (pruneImdtRels) rel_var_09870be8e1a4a08e->purge();
}

} // namespace souffle

namespace souffle {
class Stratum_add_prep_670e12a5611ce0c6 {
public:
 Stratum_add_prep_670e12a5611ce0c6(SymbolTable& symTable,RecordTable& recordTable,bool& pruneImdtRels,bool& performIO,SignalHandler*& signalHandler,std::atomic<std::size_t>& iter,std::atomic<RamDomain>& ctr,std::string& inputDirectory,std::string& outputDirectory,t_btree_iii__0_1_2__111::Type& rel_delta_add_prep_81473cce7460e2b6,t_btree_iii__0_1_2__111::Type& rel_new_add_prep_d729e5114de538fd,t_btree_i__0__2__1::Type& rel_N_913bf6e156bb077c,t_btree_iii__0_1_2__111::Type& rel_add_prep_e8dfec160429ed9e);
void run([[maybe_unused]] const std::vector<RamDomain>& args,[[maybe_unused]] std::vector<RamDomain>& ret);
private:
SymbolTable& symTable;
RecordTable& recordTable;
bool& pruneImdtRels;
bool& performIO;
SignalHandler*& signalHandler;
std::atomic<std::size_t>& iter;
std::atomic<RamDomain>& ctr;
std::string& inputDirectory;
std::string& outputDirectory;
t_btree_iii__0_1_2__111::Type* rel_delta_add_prep_81473cce7460e2b6;
t_btree_iii__0_1_2__111::Type* rel_new_add_prep_d729e5114de538fd;
t_btree_i__0__2__1::Type* rel_N_913bf6e156bb077c;
t_btree_iii__0_1_2__111::Type* rel_add_prep_e8dfec160429ed9e;
};
} // namespace souffle
namespace souffle {
 Stratum_add_prep_670e12a5611ce0c6::Stratum_add_prep_670e12a5611ce0c6(SymbolTable& symTable,RecordTable& recordTable,bool& pruneImdtRels,bool& performIO,SignalHandler*& signalHandler,std::atomic<std::size_t>& iter,std::atomic<RamDomain>& ctr,std::string& inputDirectory,std::string& outputDirectory,t_btree_iii__0_1_2__111::Type& rel_delta_add_prep_81473cce7460e2b6,t_btree_iii__0_1_2__111::Type& rel_new_add_prep_d729e5114de538fd,t_btree_i__0__2__1::Type& rel_N_913bf6e156bb077c,t_btree_iii__0_1_2__111::Type& rel_add_prep_e8dfec160429ed9e):
symTable(symTable),
recordTable(recordTable),
pruneImdtRels(pruneImdtRels),
performIO(performIO),
signalHandler(signalHandler),
iter(iter),
ctr(ctr),
inputDirectory(inputDirectory),
outputDirectory(outputDirectory),
rel_delta_add_prep_81473cce7460e2b6(&rel_delta_add_prep_81473cce7460e2b6),
rel_new_add_prep_d729e5114de538fd(&rel_new_add_prep_d729e5114de538fd),
rel_N_913bf6e156bb077c(&rel_N_913bf6e156bb077c),
rel_add_prep_e8dfec160429ed9e(&rel_add_prep_e8dfec160429ed9e){
}

void Stratum_add_prep_670e12a5611ce0c6::run([[maybe_unused]] const std::vector<RamDomain>& args,[[maybe_unused]] std::vector<RamDomain>& ret){
signalHandler->setMsg(R"_(add_prep($Var(2),$Var(1),$Add($Var(2), $Var(1))).
in file naive.dl [14:1-14:52])_");
[&](){
CREATE_OP_CONTEXT(rel_add_prep_e8dfec160429ed9e_op_ctxt,rel_add_prep_e8dfec160429ed9e->createContext());
Tuple<RamDomain,3> tuple{{ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(RamSigned(1))),ramBitCast(ramBitCast(RamSigned(2)))}}
)),ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(RamSigned(1))),ramBitCast(ramBitCast(RamSigned(1)))}}
)),ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(RamSigned(0))),ramBitCast(ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(RamSigned(1))),ramBitCast(ramBitCast(RamSigned(2)))}}
))),ramBitCast(ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(RamSigned(1))),ramBitCast(ramBitCast(RamSigned(1)))}}
)))}}
)))}}
))}};
rel_add_prep_e8dfec160429ed9e->insert(tuple,READ_OP_CONTEXT(rel_add_prep_e8dfec160429ed9e_op_ctxt));
}
();[&](){
CREATE_OP_CONTEXT(rel_delta_add_prep_81473cce7460e2b6_op_ctxt,rel_delta_add_prep_81473cce7460e2b6->createContext());
CREATE_OP_CONTEXT(rel_add_prep_e8dfec160429ed9e_op_ctxt,rel_add_prep_e8dfec160429ed9e->createContext());
for(const auto& env0 : *rel_add_prep_e8dfec160429ed9e) {
Tuple<RamDomain,3> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1]),ramBitCast(env0[2])}};
rel_delta_add_prep_81473cce7460e2b6->insert(tuple,READ_OP_CONTEXT(rel_delta_add_prep_81473cce7460e2b6_op_ctxt));
}
}
();iter = 0;
for(;;) {
signalHandler->setMsg(R"_(add_prep($Var((x+1)),id,$Add($Var((x+1)), id)) :- 
   add_prep($Var(x),_,id),
   x <= n,
   N(n).
in file naive.dl [15:1-19:15])_");
if(!(rel_delta_add_prep_81473cce7460e2b6->empty()) && !(rel_N_913bf6e156bb077c->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_delta_add_prep_81473cce7460e2b6_op_ctxt,rel_delta_add_prep_81473cce7460e2b6->createContext());
CREATE_OP_CONTEXT(rel_new_add_prep_d729e5114de538fd_op_ctxt,rel_new_add_prep_d729e5114de538fd->createContext());
CREATE_OP_CONTEXT(rel_N_913bf6e156bb077c_op_ctxt,rel_N_913bf6e156bb077c->createContext());
CREATE_OP_CONTEXT(rel_add_prep_e8dfec160429ed9e_op_ctxt,rel_add_prep_e8dfec160429ed9e->createContext());
for(const auto& env0 : *rel_delta_add_prep_81473cce7460e2b6) {
RamDomain const ref = env0[0];
if (ref == 0) continue;
const RamDomain *env1 = recordTable.unpack(ref,2);
{
if( (ramBitCast<RamDomain>(env1[0]) == ramBitCast<RamDomain>(RamSigned(1))) && !(rel_add_prep_e8dfec160429ed9e->contains(Tuple<RamDomain,3>{{ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(RamSigned(1))),ramBitCast(ramBitCast((ramBitCast<RamSigned>(env1[1]) + ramBitCast<RamSigned>(RamSigned(1)))))}}
)),ramBitCast(env0[2]),ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(RamSigned(0))),ramBitCast(ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(RamSigned(1))),ramBitCast(ramBitCast((ramBitCast<RamSigned>(env1[1]) + ramBitCast<RamSigned>(RamSigned(1)))))}}
))),ramBitCast(ramBitCast(env0[2]))}}
)))}}
))}},READ_OP_CONTEXT(rel_add_prep_e8dfec160429ed9e_op_ctxt)))) {
auto range = rel_N_913bf6e156bb077c->lowerUpperRange_2(Tuple<RamDomain,1>{{ramBitCast(env1[1])}},Tuple<RamDomain,1>{{ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_N_913bf6e156bb077c_op_ctxt));
for(const auto& env2 : range) {
if( true) {
Tuple<RamDomain,3> tuple{{ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(RamSigned(1))),ramBitCast(ramBitCast((ramBitCast<RamSigned>(env1[1]) + ramBitCast<RamSigned>(RamSigned(1)))))}}
)),ramBitCast(env0[2]),ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(RamSigned(0))),ramBitCast(ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(RamSigned(1))),ramBitCast(ramBitCast((ramBitCast<RamSigned>(env1[1]) + ramBitCast<RamSigned>(RamSigned(1)))))}}
))),ramBitCast(ramBitCast(env0[2]))}}
)))}}
))}};
rel_new_add_prep_d729e5114de538fd->insert(tuple,READ_OP_CONTEXT(rel_new_add_prep_d729e5114de538fd_op_ctxt));
break;
}
}
}
}
}
}
();}
if(rel_new_add_prep_d729e5114de538fd->empty()) break;
[&](){
CREATE_OP_CONTEXT(rel_new_add_prep_d729e5114de538fd_op_ctxt,rel_new_add_prep_d729e5114de538fd->createContext());
CREATE_OP_CONTEXT(rel_add_prep_e8dfec160429ed9e_op_ctxt,rel_add_prep_e8dfec160429ed9e->createContext());
for(const auto& env0 : *rel_new_add_prep_d729e5114de538fd) {
Tuple<RamDomain,3> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1]),ramBitCast(env0[2])}};
rel_add_prep_e8dfec160429ed9e->insert(tuple,READ_OP_CONTEXT(rel_add_prep_e8dfec160429ed9e_op_ctxt));
}
}
();std::swap(rel_delta_add_prep_81473cce7460e2b6, rel_new_add_prep_d729e5114de538fd);
rel_new_add_prep_d729e5114de538fd->purge();
iter++;
}
iter = 0;
rel_delta_add_prep_81473cce7460e2b6->purge();
rel_new_add_prep_d729e5114de538fd->purge();
}

} // namespace souffle

namespace souffle {
class Stratum_class_7ad9e07ae9eb30e9 {
public:
 Stratum_class_7ad9e07ae9eb30e9(SymbolTable& symTable,RecordTable& recordTable,bool& pruneImdtRels,bool& performIO,SignalHandler*& signalHandler,std::atomic<std::size_t>& iter,std::atomic<RamDomain>& ctr,std::string& inputDirectory,std::string& outputDirectory,t_btree_i__0__1::Type& rel_class_9017e5267072d9ea,t_btree_ii__0_1__11::Type& rel_leader_d565398e1ef92697);
void run([[maybe_unused]] const std::vector<RamDomain>& args,[[maybe_unused]] std::vector<RamDomain>& ret);
private:
SymbolTable& symTable;
RecordTable& recordTable;
bool& pruneImdtRels;
bool& performIO;
SignalHandler*& signalHandler;
std::atomic<std::size_t>& iter;
std::atomic<RamDomain>& ctr;
std::string& inputDirectory;
std::string& outputDirectory;
t_btree_i__0__1::Type* rel_class_9017e5267072d9ea;
t_btree_ii__0_1__11::Type* rel_leader_d565398e1ef92697;
};
} // namespace souffle
namespace souffle {
 Stratum_class_7ad9e07ae9eb30e9::Stratum_class_7ad9e07ae9eb30e9(SymbolTable& symTable,RecordTable& recordTable,bool& pruneImdtRels,bool& performIO,SignalHandler*& signalHandler,std::atomic<std::size_t>& iter,std::atomic<RamDomain>& ctr,std::string& inputDirectory,std::string& outputDirectory,t_btree_i__0__1::Type& rel_class_9017e5267072d9ea,t_btree_ii__0_1__11::Type& rel_leader_d565398e1ef92697):
symTable(symTable),
recordTable(recordTable),
pruneImdtRels(pruneImdtRels),
performIO(performIO),
signalHandler(signalHandler),
iter(iter),
ctr(ctr),
inputDirectory(inputDirectory),
outputDirectory(outputDirectory),
rel_class_9017e5267072d9ea(&rel_class_9017e5267072d9ea),
rel_leader_d565398e1ef92697(&rel_leader_d565398e1ef92697){
}

void Stratum_class_7ad9e07ae9eb30e9::run([[maybe_unused]] const std::vector<RamDomain>& args,[[maybe_unused]] std::vector<RamDomain>& ret){
signalHandler->setMsg(R"_(class(a) :- 
   leader(_,a).
in file naive.dl [57:1-57:26])_");
if(!(rel_leader_d565398e1ef92697->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_class_9017e5267072d9ea_op_ctxt,rel_class_9017e5267072d9ea->createContext());
CREATE_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt,rel_leader_d565398e1ef92697->createContext());
for(const auto& env0 : *rel_leader_d565398e1ef92697) {
Tuple<RamDomain,1> tuple{{ramBitCast(env0[1])}};
rel_class_9017e5267072d9ea->insert(tuple,READ_OP_CONTEXT(rel_class_9017e5267072d9ea_op_ctxt));
}
}
();}
if (performIO) {
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","a"},{"auxArity","0"},{"name","class"},{"operation","output"},{"output-dir","naive"},{"params","{\"records\": {}, \"relation\": {\"arity\": 1, \"params\": [\"a\"]}}"},{"types","{\"ADTs\": {\"+:Id\": {\"arity\": 2, \"branches\": [{\"name\": \"Add\", \"types\": [\"+:Id\", \"+:Id\"]}, {\"name\": \"Var\", \"types\": [\"i:number\"]}], \"enum\": false}}, \"records\": {}, \"relation\": {\"arity\": 1, \"types\": [\"+:Id\"]}}"}});
if (!outputDirectory.empty()) {directiveMap["output-dir"] = outputDirectory;}
IOSystem::getInstance().getWriter(directiveMap, symTable, recordTable)->writeAll(*rel_class_9017e5267072d9ea);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
}
}

} // namespace souffle

namespace souffle {
class Stratum_leader_91a62c1843cd16c8 {
public:
 Stratum_leader_91a62c1843cd16c8(SymbolTable& symTable,RecordTable& recordTable,bool& pruneImdtRels,bool& performIO,SignalHandler*& signalHandler,std::atomic<std::size_t>& iter,std::atomic<RamDomain>& ctr,std::string& inputDirectory,std::string& outputDirectory,t_eqrel& rel_eql_e1be027843ac9bc5,t_btree_ii__0_1__11::Type& rel_leader_d565398e1ef92697);
void run([[maybe_unused]] const std::vector<RamDomain>& args,[[maybe_unused]] std::vector<RamDomain>& ret);
private:
SymbolTable& symTable;
RecordTable& recordTable;
bool& pruneImdtRels;
bool& performIO;
SignalHandler*& signalHandler;
std::atomic<std::size_t>& iter;
std::atomic<RamDomain>& ctr;
std::string& inputDirectory;
std::string& outputDirectory;
t_eqrel* rel_eql_e1be027843ac9bc5;
t_btree_ii__0_1__11::Type* rel_leader_d565398e1ef92697;
};
} // namespace souffle
namespace souffle {
 Stratum_leader_91a62c1843cd16c8::Stratum_leader_91a62c1843cd16c8(SymbolTable& symTable,RecordTable& recordTable,bool& pruneImdtRels,bool& performIO,SignalHandler*& signalHandler,std::atomic<std::size_t>& iter,std::atomic<RamDomain>& ctr,std::string& inputDirectory,std::string& outputDirectory,t_eqrel& rel_eql_e1be027843ac9bc5,t_btree_ii__0_1__11::Type& rel_leader_d565398e1ef92697):
symTable(symTable),
recordTable(recordTable),
pruneImdtRels(pruneImdtRels),
performIO(performIO),
signalHandler(signalHandler),
iter(iter),
ctr(ctr),
inputDirectory(inputDirectory),
outputDirectory(outputDirectory),
rel_eql_e1be027843ac9bc5(&rel_eql_e1be027843ac9bc5),
rel_leader_d565398e1ef92697(&rel_leader_d565398e1ef92697){
}

void Stratum_leader_91a62c1843cd16c8::run([[maybe_unused]] const std::vector<RamDomain>& args,[[maybe_unused]] std::vector<RamDomain>& ret){
signalHandler->setMsg(R"_(leader(a,as(@generator_0, Id)) :- 
   eql(a,_),
   @generator_0 = min as(b0, number) : { eql(a,b0),as(b0, number) = as(b0, number) }.
in file naive.dl [54:1-54:83])_");
if(!(rel_eql_e1be027843ac9bc5->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_eql_e1be027843ac9bc5_op_ctxt,rel_eql_e1be027843ac9bc5->createContext());
CREATE_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt,rel_leader_d565398e1ef92697->createContext());
for(const auto& env0 : *rel_eql_e1be027843ac9bc5) {
Tuple<RamDomain,1> env1;
bool shouldRunNested = false;
RamSigned res0 = MAX_RAM_SIGNED;
auto range = rel_eql_e1be027843ac9bc5->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_eql_e1be027843ac9bc5_op_ctxt));
for(const auto& env1 : range) {
if( (ramBitCast<RamDomain>(env1[1]) == ramBitCast<RamDomain>(env1[1]))) {
shouldRunNested = true;
res0 = std::min(res0,ramBitCast<RamSigned>(env1[1]));
}
}
env1[0] = ramBitCast(res0);
if (shouldRunNested) {
if( (ramBitCast<RamDomain>(env1[0]) == ramBitCast<RamDomain>(env1[0]))) {
Tuple<RamDomain,2> tuple{{ramBitCast(env0[0]),ramBitCast(env1[0])}};
rel_leader_d565398e1ef92697->insert(tuple,READ_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt));
}
}
}
}
();}
if (performIO) {
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","a\tb"},{"auxArity","0"},{"name","leader"},{"operation","output"},{"output-dir","naive"},{"params","{\"records\": {}, \"relation\": {\"arity\": 2, \"params\": [\"a\", \"b\"]}}"},{"types","{\"ADTs\": {\"+:Id\": {\"arity\": 2, \"branches\": [{\"name\": \"Add\", \"types\": [\"+:Id\", \"+:Id\"]}, {\"name\": \"Var\", \"types\": [\"i:number\"]}], \"enum\": false}}, \"records\": {}, \"relation\": {\"arity\": 2, \"types\": [\"+:Id\", \"+:Id\"]}}"}});
if (!outputDirectory.empty()) {directiveMap["output-dir"] = outputDirectory;}
IOSystem::getInstance().getWriter(directiveMap, symTable, recordTable)->writeAll(*rel_leader_d565398e1ef92697);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
}
if (pruneImdtRels) rel_eql_e1be027843ac9bc5->purge();
}

} // namespace souffle

namespace souffle {
class Stratum_root_83915ac4426ff1c9 {
public:
 Stratum_root_83915ac4426ff1c9(SymbolTable& symTable,RecordTable& recordTable,bool& pruneImdtRels,bool& performIO,SignalHandler*& signalHandler,std::atomic<std::size_t>& iter,std::atomic<RamDomain>& ctr,std::string& inputDirectory,std::string& outputDirectory,t_btree_ii__0_1__11::Type& rel_leader_d565398e1ef92697,t_btree_ii__0_1__11::Type& rel_root_4971aadef59ffd68);
void run([[maybe_unused]] const std::vector<RamDomain>& args,[[maybe_unused]] std::vector<RamDomain>& ret);
private:
SymbolTable& symTable;
RecordTable& recordTable;
bool& pruneImdtRels;
bool& performIO;
SignalHandler*& signalHandler;
std::atomic<std::size_t>& iter;
std::atomic<RamDomain>& ctr;
std::string& inputDirectory;
std::string& outputDirectory;
t_btree_ii__0_1__11::Type* rel_leader_d565398e1ef92697;
t_btree_ii__0_1__11::Type* rel_root_4971aadef59ffd68;
};
} // namespace souffle
namespace souffle {
 Stratum_root_83915ac4426ff1c9::Stratum_root_83915ac4426ff1c9(SymbolTable& symTable,RecordTable& recordTable,bool& pruneImdtRels,bool& performIO,SignalHandler*& signalHandler,std::atomic<std::size_t>& iter,std::atomic<RamDomain>& ctr,std::string& inputDirectory,std::string& outputDirectory,t_btree_ii__0_1__11::Type& rel_leader_d565398e1ef92697,t_btree_ii__0_1__11::Type& rel_root_4971aadef59ffd68):
symTable(symTable),
recordTable(recordTable),
pruneImdtRels(pruneImdtRels),
performIO(performIO),
signalHandler(signalHandler),
iter(iter),
ctr(ctr),
inputDirectory(inputDirectory),
outputDirectory(outputDirectory),
rel_leader_d565398e1ef92697(&rel_leader_d565398e1ef92697),
rel_root_4971aadef59ffd68(&rel_root_4971aadef59ffd68){
}

void Stratum_root_83915ac4426ff1c9::run([[maybe_unused]] const std::vector<RamDomain>& args,[[maybe_unused]] std::vector<RamDomain>& ret){
signalHandler->setMsg(R"_(root(1,a) :- 
   leader($Add($Var(4), $Add($Var(3), $Add($Var(2), $Var(1)))),a).
in file naive.dl [60:1-60:79])_");
if(!(rel_leader_d565398e1ef92697->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt,rel_leader_d565398e1ef92697->createContext());
CREATE_OP_CONTEXT(rel_root_4971aadef59ffd68_op_ctxt,rel_root_4971aadef59ffd68->createContext());
for(const auto& env0 : *rel_leader_d565398e1ef92697) {
RamDomain const ref = env0[0];
if (ref == 0) continue;
const RamDomain *env1 = recordTable.unpack(ref,2);
{
if( (ramBitCast<RamDomain>(env1[0]) == ramBitCast<RamDomain>(RamSigned(0)))) {
RamDomain const ref = env1[1];
if (ref == 0) continue;
const RamDomain *env2 = recordTable.unpack(ref,2);
{
RamDomain const ref = env2[0];
if (ref == 0) continue;
const RamDomain *env3 = recordTable.unpack(ref,2);
{
if( (ramBitCast<RamDomain>(env3[1]) == ramBitCast<RamDomain>(RamSigned(4))) && (ramBitCast<RamDomain>(env3[0]) == ramBitCast<RamDomain>(RamSigned(1)))) {
RamDomain const ref = env2[1];
if (ref == 0) continue;
const RamDomain *env4 = recordTable.unpack(ref,2);
{
if( (ramBitCast<RamDomain>(env4[0]) == ramBitCast<RamDomain>(RamSigned(0)))) {
RamDomain const ref = env4[1];
if (ref == 0) continue;
const RamDomain *env5 = recordTable.unpack(ref,2);
{
RamDomain const ref = env5[0];
if (ref == 0) continue;
const RamDomain *env6 = recordTable.unpack(ref,2);
{
if( (ramBitCast<RamDomain>(env6[1]) == ramBitCast<RamDomain>(RamSigned(3))) && (ramBitCast<RamDomain>(env6[0]) == ramBitCast<RamDomain>(RamSigned(1)))) {
RamDomain const ref = env5[1];
if (ref == 0) continue;
const RamDomain *env7 = recordTable.unpack(ref,2);
{
if( (ramBitCast<RamDomain>(env7[0]) == ramBitCast<RamDomain>(RamSigned(0)))) {
RamDomain const ref = env7[1];
if (ref == 0) continue;
const RamDomain *env8 = recordTable.unpack(ref,2);
{
RamDomain const ref = env8[0];
if (ref == 0) continue;
const RamDomain *env9 = recordTable.unpack(ref,2);
{
if( (ramBitCast<RamDomain>(env9[1]) == ramBitCast<RamDomain>(RamSigned(2))) && (ramBitCast<RamDomain>(env9[0]) == ramBitCast<RamDomain>(RamSigned(1)))) {
RamDomain const ref = env8[1];
if (ref == 0) continue;
const RamDomain *env10 = recordTable.unpack(ref,2);
{
if( (ramBitCast<RamDomain>(env10[1]) == ramBitCast<RamDomain>(RamSigned(1))) && (ramBitCast<RamDomain>(env10[0]) == ramBitCast<RamDomain>(RamSigned(1)))) {
Tuple<RamDomain,2> tuple{{ramBitCast(RamSigned(1)),ramBitCast(env0[1])}};
rel_root_4971aadef59ffd68->insert(tuple,READ_OP_CONTEXT(rel_root_4971aadef59ffd68_op_ctxt));
}
}
}
}
}
}
}
}
}
}
}
}
}
}
}
}
}
}
}
();}
signalHandler->setMsg(R"_(root(2,a) :- 
   leader($Add($Var(1), $Add($Var(2), $Add($Var(3), $Var(4)))),a).
in file naive.dl [61:1-61:79])_");
if(!(rel_leader_d565398e1ef92697->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt,rel_leader_d565398e1ef92697->createContext());
CREATE_OP_CONTEXT(rel_root_4971aadef59ffd68_op_ctxt,rel_root_4971aadef59ffd68->createContext());
for(const auto& env0 : *rel_leader_d565398e1ef92697) {
RamDomain const ref = env0[0];
if (ref == 0) continue;
const RamDomain *env1 = recordTable.unpack(ref,2);
{
if( (ramBitCast<RamDomain>(env1[0]) == ramBitCast<RamDomain>(RamSigned(0)))) {
RamDomain const ref = env1[1];
if (ref == 0) continue;
const RamDomain *env2 = recordTable.unpack(ref,2);
{
RamDomain const ref = env2[0];
if (ref == 0) continue;
const RamDomain *env3 = recordTable.unpack(ref,2);
{
if( (ramBitCast<RamDomain>(env3[1]) == ramBitCast<RamDomain>(RamSigned(1))) && (ramBitCast<RamDomain>(env3[0]) == ramBitCast<RamDomain>(RamSigned(1)))) {
RamDomain const ref = env2[1];
if (ref == 0) continue;
const RamDomain *env4 = recordTable.unpack(ref,2);
{
if( (ramBitCast<RamDomain>(env4[0]) == ramBitCast<RamDomain>(RamSigned(0)))) {
RamDomain const ref = env4[1];
if (ref == 0) continue;
const RamDomain *env5 = recordTable.unpack(ref,2);
{
RamDomain const ref = env5[0];
if (ref == 0) continue;
const RamDomain *env6 = recordTable.unpack(ref,2);
{
if( (ramBitCast<RamDomain>(env6[1]) == ramBitCast<RamDomain>(RamSigned(2))) && (ramBitCast<RamDomain>(env6[0]) == ramBitCast<RamDomain>(RamSigned(1)))) {
RamDomain const ref = env5[1];
if (ref == 0) continue;
const RamDomain *env7 = recordTable.unpack(ref,2);
{
if( (ramBitCast<RamDomain>(env7[0]) == ramBitCast<RamDomain>(RamSigned(0)))) {
RamDomain const ref = env7[1];
if (ref == 0) continue;
const RamDomain *env8 = recordTable.unpack(ref,2);
{
RamDomain const ref = env8[0];
if (ref == 0) continue;
const RamDomain *env9 = recordTable.unpack(ref,2);
{
if( (ramBitCast<RamDomain>(env9[1]) == ramBitCast<RamDomain>(RamSigned(3))) && (ramBitCast<RamDomain>(env9[0]) == ramBitCast<RamDomain>(RamSigned(1)))) {
RamDomain const ref = env8[1];
if (ref == 0) continue;
const RamDomain *env10 = recordTable.unpack(ref,2);
{
if( (ramBitCast<RamDomain>(env10[1]) == ramBitCast<RamDomain>(RamSigned(4))) && (ramBitCast<RamDomain>(env10[0]) == ramBitCast<RamDomain>(RamSigned(1)))) {
Tuple<RamDomain,2> tuple{{ramBitCast(RamSigned(2)),ramBitCast(env0[1])}};
rel_root_4971aadef59ffd68->insert(tuple,READ_OP_CONTEXT(rel_root_4971aadef59ffd68_op_ctxt));
}
}
}
}
}
}
}
}
}
}
}
}
}
}
}
}
}
}
}
();}
if (performIO) {
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","i\ta"},{"auxArity","0"},{"name","root"},{"operation","output"},{"output-dir","naive"},{"params","{\"records\": {}, \"relation\": {\"arity\": 2, \"params\": [\"i\", \"a\"]}}"},{"types","{\"ADTs\": {\"+:Id\": {\"arity\": 2, \"branches\": [{\"name\": \"Add\", \"types\": [\"+:Id\", \"+:Id\"]}, {\"name\": \"Var\", \"types\": [\"i:number\"]}], \"enum\": false}}, \"records\": {}, \"relation\": {\"arity\": 2, \"types\": [\"i:number\", \"+:Id\"]}}"}});
if (!outputDirectory.empty()) {directiveMap["output-dir"] = outputDirectory;}
IOSystem::getInstance().getWriter(directiveMap, symTable, recordTable)->writeAll(*rel_root_4971aadef59ffd68);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
}
if (pruneImdtRels) rel_leader_d565398e1ef92697->purge();
}

} // namespace souffle

namespace souffle {
class Stratum_var_48e96bfc8149a95b {
public:
 Stratum_var_48e96bfc8149a95b(SymbolTable& symTable,RecordTable& recordTable,bool& pruneImdtRels,bool& performIO,SignalHandler*& signalHandler,std::atomic<std::size_t>& iter,std::atomic<RamDomain>& ctr,std::string& inputDirectory,std::string& outputDirectory,t_btree_i__0__2__1::Type& rel_N_913bf6e156bb077c,t_btree_iii__0_1_2__111::Type& rel_add_prep_e8dfec160429ed9e,t_btree_ii__0_1__11__10::Type& rel_var_09870be8e1a4a08e);
void run([[maybe_unused]] const std::vector<RamDomain>& args,[[maybe_unused]] std::vector<RamDomain>& ret);
private:
SymbolTable& symTable;
RecordTable& recordTable;
bool& pruneImdtRels;
bool& performIO;
SignalHandler*& signalHandler;
std::atomic<std::size_t>& iter;
std::atomic<RamDomain>& ctr;
std::string& inputDirectory;
std::string& outputDirectory;
t_btree_i__0__2__1::Type* rel_N_913bf6e156bb077c;
t_btree_iii__0_1_2__111::Type* rel_add_prep_e8dfec160429ed9e;
t_btree_ii__0_1__11__10::Type* rel_var_09870be8e1a4a08e;
};
} // namespace souffle
namespace souffle {
 Stratum_var_48e96bfc8149a95b::Stratum_var_48e96bfc8149a95b(SymbolTable& symTable,RecordTable& recordTable,bool& pruneImdtRels,bool& performIO,SignalHandler*& signalHandler,std::atomic<std::size_t>& iter,std::atomic<RamDomain>& ctr,std::string& inputDirectory,std::string& outputDirectory,t_btree_i__0__2__1::Type& rel_N_913bf6e156bb077c,t_btree_iii__0_1_2__111::Type& rel_add_prep_e8dfec160429ed9e,t_btree_ii__0_1__11__10::Type& rel_var_09870be8e1a4a08e):
symTable(symTable),
recordTable(recordTable),
pruneImdtRels(pruneImdtRels),
performIO(performIO),
signalHandler(signalHandler),
iter(iter),
ctr(ctr),
inputDirectory(inputDirectory),
outputDirectory(outputDirectory),
rel_N_913bf6e156bb077c(&rel_N_913bf6e156bb077c),
rel_add_prep_e8dfec160429ed9e(&rel_add_prep_e8dfec160429ed9e),
rel_var_09870be8e1a4a08e(&rel_var_09870be8e1a4a08e){
}

void Stratum_var_48e96bfc8149a95b::run([[maybe_unused]] const std::vector<RamDomain>& args,[[maybe_unused]] std::vector<RamDomain>& ret){
signalHandler->setMsg(R"_(var(1,$Var(1)).
in file naive.dl [12:1-12:17])_");
[&](){
CREATE_OP_CONTEXT(rel_var_09870be8e1a4a08e_op_ctxt,rel_var_09870be8e1a4a08e->createContext());
Tuple<RamDomain,2> tuple{{ramBitCast(RamSigned(1)),ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(RamSigned(1))),ramBitCast(ramBitCast(RamSigned(1)))}}
))}};
rel_var_09870be8e1a4a08e->insert(tuple,READ_OP_CONTEXT(rel_var_09870be8e1a4a08e_op_ctxt));
}
();signalHandler->setMsg(R"_(var(2,$Var(2)).
in file naive.dl [13:1-13:17])_");
[&](){
CREATE_OP_CONTEXT(rel_var_09870be8e1a4a08e_op_ctxt,rel_var_09870be8e1a4a08e->createContext());
Tuple<RamDomain,2> tuple{{ramBitCast(RamSigned(2)),ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(RamSigned(1))),ramBitCast(ramBitCast(RamSigned(2)))}}
))}};
rel_var_09870be8e1a4a08e->insert(tuple,READ_OP_CONTEXT(rel_var_09870be8e1a4a08e_op_ctxt));
}
();signalHandler->setMsg(R"_(var((x+1),$Var((x+1))) :- 
   add_prep($Var(x),_,_),
   x <= n,
   N(n).
in file naive.dl [15:1-19:15])_");
if(!(rel_add_prep_e8dfec160429ed9e->empty()) && !(rel_N_913bf6e156bb077c->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_N_913bf6e156bb077c_op_ctxt,rel_N_913bf6e156bb077c->createContext());
CREATE_OP_CONTEXT(rel_add_prep_e8dfec160429ed9e_op_ctxt,rel_add_prep_e8dfec160429ed9e->createContext());
CREATE_OP_CONTEXT(rel_var_09870be8e1a4a08e_op_ctxt,rel_var_09870be8e1a4a08e->createContext());
for(const auto& env0 : *rel_add_prep_e8dfec160429ed9e) {
RamDomain const ref = env0[0];
if (ref == 0) continue;
const RamDomain *env1 = recordTable.unpack(ref,2);
{
if( (ramBitCast<RamDomain>(env1[0]) == ramBitCast<RamDomain>(RamSigned(1)))) {
auto range = rel_N_913bf6e156bb077c->lowerUpperRange_2(Tuple<RamDomain,1>{{ramBitCast(env1[1])}},Tuple<RamDomain,1>{{ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_N_913bf6e156bb077c_op_ctxt));
for(const auto& env2 : range) {
if( true) {
Tuple<RamDomain,2> tuple{{ramBitCast((ramBitCast<RamSigned>(env1[1]) + ramBitCast<RamSigned>(RamSigned(1)))),ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(RamSigned(1))),ramBitCast(ramBitCast((ramBitCast<RamSigned>(env1[1]) + ramBitCast<RamSigned>(RamSigned(1)))))}}
))}};
rel_var_09870be8e1a4a08e->insert(tuple,READ_OP_CONTEXT(rel_var_09870be8e1a4a08e_op_ctxt));
break;
}
}
}
}
}
}
();}
if (pruneImdtRels) rel_N_913bf6e156bb077c->purge();
}

} // namespace souffle

namespace souffle {
class Sf_naive: public SouffleProgram {
public:
 Sf_naive();
 ~Sf_naive();
void run();
void runAll(std::string inputDirectoryArg = "",std::string outputDirectoryArg = "",bool performIOArg = true,bool pruneImdtRelsArg = true);
void printAll([[maybe_unused]] std::string outputDirectoryArg = "");
void loadAll([[maybe_unused]] std::string inputDirectoryArg = "");
void dumpInputs();
void dumpOutputs();
SymbolTable& getSymbolTable();
RecordTable& getRecordTable();
void setNumThreads(std::size_t numThreadsValue);
void executeSubroutine(std::string name,const std::vector<RamDomain>& args,std::vector<RamDomain>& ret);
private:
void runFunction(std::string inputDirectoryArg,std::string outputDirectoryArg,bool performIOArg,bool pruneImdtRelsArg);
SymbolTableImpl symTable;
SpecializedRecordTable<0,2> recordTable;
Own<t_btree_i__0__2__1::Type> rel_N_913bf6e156bb077c;
souffle::RelationWrapper<t_btree_i__0__2__1::Type> wrapper_rel_N_913bf6e156bb077c;
Own<t_btree_iii__0_1_2__111::Type> rel_add_prep_e8dfec160429ed9e;
souffle::RelationWrapper<t_btree_iii__0_1_2__111::Type> wrapper_rel_add_prep_e8dfec160429ed9e;
Own<t_btree_iii__0_1_2__111::Type> rel_delta_add_prep_81473cce7460e2b6;
Own<t_btree_iii__0_1_2__111::Type> rel_new_add_prep_d729e5114de538fd;
Own<t_btree_ii__0_1__11__10::Type> rel_var_09870be8e1a4a08e;
souffle::RelationWrapper<t_btree_ii__0_1__11__10::Type> wrapper_rel_var_09870be8e1a4a08e;
Own<t_btree_iii__0_1_2__100__110__111::Type> rel_add_48c57da858454f79;
souffle::RelationWrapper<t_btree_iii__0_1_2__100__110__111::Type> wrapper_rel_add_48c57da858454f79;
Own<t_btree_iii__0_1_2__100__110__111::Type> rel_delta_add_241d705dc2fb23df;
Own<t_btree_iii__0_1_2__100__110__111::Type> rel_new_add_954a8c50e586f068;
Own<t_eqrel> rel_eql_e1be027843ac9bc5;
souffle::RelationWrapper<t_eqrel> wrapper_rel_eql_e1be027843ac9bc5;
Own<t_eqrel> rel_delta_eql_fdc75db4daac3372;
Own<t_eqrel> rel_new_eql_10ebb01129546352;
Own<t_btree_ii__0_1__11::Type> rel_leader_d565398e1ef92697;
souffle::RelationWrapper<t_btree_ii__0_1__11::Type> wrapper_rel_leader_d565398e1ef92697;
Own<t_btree_i__0__1::Type> rel_class_9017e5267072d9ea;
souffle::RelationWrapper<t_btree_i__0__1::Type> wrapper_rel_class_9017e5267072d9ea;
Own<t_btree_ii__0_1__11::Type> rel_root_4971aadef59ffd68;
souffle::RelationWrapper<t_btree_ii__0_1__11::Type> wrapper_rel_root_4971aadef59ffd68;
Stratum_N_2fa3d15dc185d227 stratum_N_f2fd84e3ee54ddcf;
Stratum_add_ed981d530a6b23bd stratum_add_14722fa4ca06c6d9;
Stratum_add_prep_670e12a5611ce0c6 stratum_add_prep_ad75c73511997080;
Stratum_class_7ad9e07ae9eb30e9 stratum_class_a21f43f864200ec6;
Stratum_leader_91a62c1843cd16c8 stratum_leader_5c45589c007cb28e;
Stratum_root_83915ac4426ff1c9 stratum_root_97ddb9257bc55be8;
Stratum_var_48e96bfc8149a95b stratum_var_393b9b316b2f7ec7;
std::string inputDirectory;
std::string outputDirectory;
SignalHandler* signalHandler{SignalHandler::instance()};
std::atomic<RamDomain> ctr{};
std::atomic<std::size_t> iter{};
};
} // namespace souffle
namespace souffle {
 Sf_naive::Sf_naive():
symTable(),
recordTable(),
rel_N_913bf6e156bb077c(mk<t_btree_i__0__2__1::Type>()),
wrapper_rel_N_913bf6e156bb077c(0, *rel_N_913bf6e156bb077c, *this, "N", std::array<const char *,1>{{"i:number"}}, std::array<const char *,1>{{"n"}}, 0),
rel_add_prep_e8dfec160429ed9e(mk<t_btree_iii__0_1_2__111::Type>()),
wrapper_rel_add_prep_e8dfec160429ed9e(1, *rel_add_prep_e8dfec160429ed9e, *this, "add_prep", std::array<const char *,3>{{"+:Id","+:Id","+:Id"}}, std::array<const char *,3>{{"x","y","c"}}, 0),
rel_delta_add_prep_81473cce7460e2b6(mk<t_btree_iii__0_1_2__111::Type>()),
rel_new_add_prep_d729e5114de538fd(mk<t_btree_iii__0_1_2__111::Type>()),
rel_var_09870be8e1a4a08e(mk<t_btree_ii__0_1__11__10::Type>()),
wrapper_rel_var_09870be8e1a4a08e(2, *rel_var_09870be8e1a4a08e, *this, "var", std::array<const char *,2>{{"i:number","+:Id"}}, std::array<const char *,2>{{"x","c"}}, 0),
rel_add_48c57da858454f79(mk<t_btree_iii__0_1_2__100__110__111::Type>()),
wrapper_rel_add_48c57da858454f79(3, *rel_add_48c57da858454f79, *this, "add", std::array<const char *,3>{{"+:Id","+:Id","+:Id"}}, std::array<const char *,3>{{"x","y","c"}}, 0),
rel_delta_add_241d705dc2fb23df(mk<t_btree_iii__0_1_2__100__110__111::Type>()),
rel_new_add_954a8c50e586f068(mk<t_btree_iii__0_1_2__100__110__111::Type>()),
rel_eql_e1be027843ac9bc5(mk<t_eqrel>()),
wrapper_rel_eql_e1be027843ac9bc5(4, *rel_eql_e1be027843ac9bc5, *this, "eql", std::array<const char *,2>{{"+:Id","+:Id"}}, std::array<const char *,2>{{"x","y"}}, 0),
rel_delta_eql_fdc75db4daac3372(mk<t_eqrel>()),
rel_new_eql_10ebb01129546352(mk<t_eqrel>()),
rel_leader_d565398e1ef92697(mk<t_btree_ii__0_1__11::Type>()),
wrapper_rel_leader_d565398e1ef92697(5, *rel_leader_d565398e1ef92697, *this, "leader", std::array<const char *,2>{{"+:Id","+:Id"}}, std::array<const char *,2>{{"a","b"}}, 0),
rel_class_9017e5267072d9ea(mk<t_btree_i__0__1::Type>()),
wrapper_rel_class_9017e5267072d9ea(6, *rel_class_9017e5267072d9ea, *this, "class", std::array<const char *,1>{{"+:Id"}}, std::array<const char *,1>{{"a"}}, 0),
rel_root_4971aadef59ffd68(mk<t_btree_ii__0_1__11::Type>()),
wrapper_rel_root_4971aadef59ffd68(7, *rel_root_4971aadef59ffd68, *this, "root", std::array<const char *,2>{{"i:number","+:Id"}}, std::array<const char *,2>{{"i","a"}}, 0),
stratum_N_f2fd84e3ee54ddcf(symTable,recordTable,pruneImdtRels,performIO,signalHandler,iter,ctr,inputDirectory,outputDirectory,*rel_N_913bf6e156bb077c),
stratum_add_14722fa4ca06c6d9(symTable,recordTable,pruneImdtRels,performIO,signalHandler,iter,ctr,inputDirectory,outputDirectory,*rel_delta_add_241d705dc2fb23df,*rel_delta_eql_fdc75db4daac3372,*rel_new_add_954a8c50e586f068,*rel_new_eql_10ebb01129546352,*rel_add_48c57da858454f79,*rel_add_prep_e8dfec160429ed9e,*rel_eql_e1be027843ac9bc5,*rel_var_09870be8e1a4a08e),
stratum_add_prep_ad75c73511997080(symTable,recordTable,pruneImdtRels,performIO,signalHandler,iter,ctr,inputDirectory,outputDirectory,*rel_delta_add_prep_81473cce7460e2b6,*rel_new_add_prep_d729e5114de538fd,*rel_N_913bf6e156bb077c,*rel_add_prep_e8dfec160429ed9e),
stratum_class_a21f43f864200ec6(symTable,recordTable,pruneImdtRels,performIO,signalHandler,iter,ctr,inputDirectory,outputDirectory,*rel_class_9017e5267072d9ea,*rel_leader_d565398e1ef92697),
stratum_leader_5c45589c007cb28e(symTable,recordTable,pruneImdtRels,performIO,signalHandler,iter,ctr,inputDirectory,outputDirectory,*rel_eql_e1be027843ac9bc5,*rel_leader_d565398e1ef92697),
stratum_root_97ddb9257bc55be8(symTable,recordTable,pruneImdtRels,performIO,signalHandler,iter,ctr,inputDirectory,outputDirectory,*rel_leader_d565398e1ef92697,*rel_root_4971aadef59ffd68),
stratum_var_393b9b316b2f7ec7(symTable,recordTable,pruneImdtRels,performIO,signalHandler,iter,ctr,inputDirectory,outputDirectory,*rel_N_913bf6e156bb077c,*rel_add_prep_e8dfec160429ed9e,*rel_var_09870be8e1a4a08e){
addRelation("N", wrapper_rel_N_913bf6e156bb077c, true, false);
addRelation("add_prep", wrapper_rel_add_prep_e8dfec160429ed9e, false, false);
addRelation("var", wrapper_rel_var_09870be8e1a4a08e, false, false);
addRelation("add", wrapper_rel_add_48c57da858454f79, false, true);
addRelation("eql", wrapper_rel_eql_e1be027843ac9bc5, false, false);
addRelation("leader", wrapper_rel_leader_d565398e1ef92697, false, true);
addRelation("class", wrapper_rel_class_9017e5267072d9ea, false, true);
addRelation("root", wrapper_rel_root_4971aadef59ffd68, false, true);
}

 Sf_naive::~Sf_naive(){
}

void Sf_naive::runFunction(std::string inputDirectoryArg,std::string outputDirectoryArg,bool performIOArg,bool pruneImdtRelsArg){

    this->inputDirectory  = std::move(inputDirectoryArg);
    this->outputDirectory = std::move(outputDirectoryArg);
    this->performIO       = performIOArg;
    this->pruneImdtRels   = pruneImdtRelsArg;

    // set default threads (in embedded mode)
    // if this is not set, and omp is used, the default omp setting of number of cores is used.
#if defined(_OPENMP)
    if (0 < getNumThreads()) { omp_set_num_threads(static_cast<int>(getNumThreads())); }
#endif

    signalHandler->set();
// -- query evaluation --
{
 std::vector<RamDomain> args, ret;
stratum_N_f2fd84e3ee54ddcf.run(args, ret);
}
{
 std::vector<RamDomain> args, ret;
stratum_add_prep_ad75c73511997080.run(args, ret);
}
{
 std::vector<RamDomain> args, ret;
stratum_var_393b9b316b2f7ec7.run(args, ret);
}
{
 std::vector<RamDomain> args, ret;
stratum_add_14722fa4ca06c6d9.run(args, ret);
}
{
 std::vector<RamDomain> args, ret;
stratum_leader_5c45589c007cb28e.run(args, ret);
}
{
 std::vector<RamDomain> args, ret;
stratum_class_a21f43f864200ec6.run(args, ret);
}
{
 std::vector<RamDomain> args, ret;
stratum_root_97ddb9257bc55be8.run(args, ret);
}

// -- relation hint statistics --
signalHandler->reset();
}

void Sf_naive::run(){
runFunction("", "", false, false);
}

void Sf_naive::runAll(std::string inputDirectoryArg,std::string outputDirectoryArg,bool performIOArg,bool pruneImdtRelsArg){
runFunction(inputDirectoryArg, outputDirectoryArg, performIOArg, pruneImdtRelsArg);
}

void Sf_naive::printAll([[maybe_unused]] std::string outputDirectoryArg){
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","x\ty\tc"},{"auxArity","0"},{"name","add"},{"operation","output"},{"output-dir","naive"},{"params","{\"records\": {}, \"relation\": {\"arity\": 3, \"params\": [\"x\", \"y\", \"c\"]}}"},{"types","{\"ADTs\": {\"+:Id\": {\"arity\": 2, \"branches\": [{\"name\": \"Add\", \"types\": [\"+:Id\", \"+:Id\"]}, {\"name\": \"Var\", \"types\": [\"i:number\"]}], \"enum\": false}}, \"records\": {}, \"relation\": {\"arity\": 3, \"types\": [\"+:Id\", \"+:Id\", \"+:Id\"]}}"}});
if (!outputDirectoryArg.empty()) {directiveMap["output-dir"] = outputDirectoryArg;}
IOSystem::getInstance().getWriter(directiveMap, symTable, recordTable)->writeAll(*rel_add_48c57da858454f79);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","x\ty\tc"},{"auxArity","0"},{"name","add"},{"operation","output"},{"output-dir","naive"},{"params","{\"records\": {}, \"relation\": {\"arity\": 3, \"params\": [\"x\", \"y\", \"c\"]}}"},{"types","{\"ADTs\": {\"+:Id\": {\"arity\": 2, \"branches\": [{\"name\": \"Add\", \"types\": [\"+:Id\", \"+:Id\"]}, {\"name\": \"Var\", \"types\": [\"i:number\"]}], \"enum\": false}}, \"records\": {}, \"relation\": {\"arity\": 3, \"types\": [\"+:Id\", \"+:Id\", \"+:Id\"]}}"}});
if (!outputDirectoryArg.empty()) {directiveMap["output-dir"] = outputDirectoryArg;}
IOSystem::getInstance().getWriter(directiveMap, symTable, recordTable)->writeAll(*rel_add_48c57da858454f79);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","a\tb"},{"auxArity","0"},{"name","leader"},{"operation","output"},{"output-dir","naive"},{"params","{\"records\": {}, \"relation\": {\"arity\": 2, \"params\": [\"a\", \"b\"]}}"},{"types","{\"ADTs\": {\"+:Id\": {\"arity\": 2, \"branches\": [{\"name\": \"Add\", \"types\": [\"+:Id\", \"+:Id\"]}, {\"name\": \"Var\", \"types\": [\"i:number\"]}], \"enum\": false}}, \"records\": {}, \"relation\": {\"arity\": 2, \"types\": [\"+:Id\", \"+:Id\"]}}"}});
if (!outputDirectoryArg.empty()) {directiveMap["output-dir"] = outputDirectoryArg;}
IOSystem::getInstance().getWriter(directiveMap, symTable, recordTable)->writeAll(*rel_leader_d565398e1ef92697);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","a"},{"auxArity","0"},{"name","class"},{"operation","output"},{"output-dir","naive"},{"params","{\"records\": {}, \"relation\": {\"arity\": 1, \"params\": [\"a\"]}}"},{"types","{\"ADTs\": {\"+:Id\": {\"arity\": 2, \"branches\": [{\"name\": \"Add\", \"types\": [\"+:Id\", \"+:Id\"]}, {\"name\": \"Var\", \"types\": [\"i:number\"]}], \"enum\": false}}, \"records\": {}, \"relation\": {\"arity\": 1, \"types\": [\"+:Id\"]}}"}});
if (!outputDirectoryArg.empty()) {directiveMap["output-dir"] = outputDirectoryArg;}
IOSystem::getInstance().getWriter(directiveMap, symTable, recordTable)->writeAll(*rel_class_9017e5267072d9ea);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","i\ta"},{"auxArity","0"},{"name","root"},{"operation","output"},{"output-dir","naive"},{"params","{\"records\": {}, \"relation\": {\"arity\": 2, \"params\": [\"i\", \"a\"]}}"},{"types","{\"ADTs\": {\"+:Id\": {\"arity\": 2, \"branches\": [{\"name\": \"Add\", \"types\": [\"+:Id\", \"+:Id\"]}, {\"name\": \"Var\", \"types\": [\"i:number\"]}], \"enum\": false}}, \"records\": {}, \"relation\": {\"arity\": 2, \"types\": [\"i:number\", \"+:Id\"]}}"}});
if (!outputDirectoryArg.empty()) {directiveMap["output-dir"] = outputDirectoryArg;}
IOSystem::getInstance().getWriter(directiveMap, symTable, recordTable)->writeAll(*rel_root_4971aadef59ffd68);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
}

void Sf_naive::loadAll([[maybe_unused]] std::string inputDirectoryArg){
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","n"},{"auxArity","0"},{"fact-dir","."},{"filename","N.in"},{"name","N"},{"operation","input"},{"params","{\"records\": {}, \"relation\": {\"arity\": 1, \"params\": [\"n\"]}}"},{"types","{\"ADTs\": {\"+:Id\": {\"arity\": 2, \"branches\": [{\"name\": \"Add\", \"types\": [\"+:Id\", \"+:Id\"]}, {\"name\": \"Var\", \"types\": [\"i:number\"]}], \"enum\": false}}, \"records\": {}, \"relation\": {\"arity\": 1, \"types\": [\"i:number\"]}}"}});
if (!inputDirectoryArg.empty()) {directiveMap["fact-dir"] = inputDirectoryArg;}
IOSystem::getInstance().getReader(directiveMap, symTable, recordTable)->readAll(*rel_N_913bf6e156bb077c);
} catch (std::exception& e) {std::cerr << "Error loading N data: " << e.what() << '\n';}
}

void Sf_naive::dumpInputs(){
try {std::map<std::string, std::string> rwOperation;
rwOperation["IO"] = "stdout";
rwOperation["name"] = "N";
rwOperation["types"] = "{\"relation\": {\"arity\": 1, \"auxArity\": 0, \"types\": [\"i:number\"]}}";
IOSystem::getInstance().getWriter(rwOperation, symTable, recordTable)->writeAll(*rel_N_913bf6e156bb077c);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
}

void Sf_naive::dumpOutputs(){
try {std::map<std::string, std::string> rwOperation;
rwOperation["IO"] = "stdout";
rwOperation["name"] = "add";
rwOperation["types"] = "{\"relation\": {\"arity\": 3, \"auxArity\": 0, \"types\": [\"+:Id\", \"+:Id\", \"+:Id\"]}}";
IOSystem::getInstance().getWriter(rwOperation, symTable, recordTable)->writeAll(*rel_add_48c57da858454f79);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
try {std::map<std::string, std::string> rwOperation;
rwOperation["IO"] = "stdout";
rwOperation["name"] = "add";
rwOperation["types"] = "{\"relation\": {\"arity\": 3, \"auxArity\": 0, \"types\": [\"+:Id\", \"+:Id\", \"+:Id\"]}}";
IOSystem::getInstance().getWriter(rwOperation, symTable, recordTable)->writeAll(*rel_add_48c57da858454f79);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
try {std::map<std::string, std::string> rwOperation;
rwOperation["IO"] = "stdout";
rwOperation["name"] = "leader";
rwOperation["types"] = "{\"relation\": {\"arity\": 2, \"auxArity\": 0, \"types\": [\"+:Id\", \"+:Id\"]}}";
IOSystem::getInstance().getWriter(rwOperation, symTable, recordTable)->writeAll(*rel_leader_d565398e1ef92697);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
try {std::map<std::string, std::string> rwOperation;
rwOperation["IO"] = "stdout";
rwOperation["name"] = "class";
rwOperation["types"] = "{\"relation\": {\"arity\": 1, \"auxArity\": 0, \"types\": [\"+:Id\"]}}";
IOSystem::getInstance().getWriter(rwOperation, symTable, recordTable)->writeAll(*rel_class_9017e5267072d9ea);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
try {std::map<std::string, std::string> rwOperation;
rwOperation["IO"] = "stdout";
rwOperation["name"] = "root";
rwOperation["types"] = "{\"relation\": {\"arity\": 2, \"auxArity\": 0, \"types\": [\"i:number\", \"+:Id\"]}}";
IOSystem::getInstance().getWriter(rwOperation, symTable, recordTable)->writeAll(*rel_root_4971aadef59ffd68);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
}

SymbolTable& Sf_naive::getSymbolTable(){
return symTable;
}

RecordTable& Sf_naive::getRecordTable(){
return recordTable;
}

void Sf_naive::setNumThreads(std::size_t numThreadsValue){
SouffleProgram::setNumThreads(numThreadsValue);
symTable.setNumLanes(getNumThreads());
recordTable.setNumLanes(getNumThreads());
}

void Sf_naive::executeSubroutine(std::string name,const std::vector<RamDomain>& args,std::vector<RamDomain>& ret){
if (name == "N") {
stratum_N_f2fd84e3ee54ddcf.run(args, ret);
return;}
if (name == "add") {
stratum_add_14722fa4ca06c6d9.run(args, ret);
return;}
if (name == "add_prep") {
stratum_add_prep_ad75c73511997080.run(args, ret);
return;}
if (name == "class") {
stratum_class_a21f43f864200ec6.run(args, ret);
return;}
if (name == "leader") {
stratum_leader_5c45589c007cb28e.run(args, ret);
return;}
if (name == "root") {
stratum_root_97ddb9257bc55be8.run(args, ret);
return;}
if (name == "var") {
stratum_var_393b9b316b2f7ec7.run(args, ret);
return;}
fatal(("unknown subroutine " + name).c_str());
}

} // namespace souffle
namespace souffle {
SouffleProgram *newInstance_naive(){return new Sf_naive;}
SymbolTable *getST_naive(SouffleProgram *p){return &reinterpret_cast<Sf_naive*>(p)->getSymbolTable();}
} // namespace souffle

#ifndef __EMBEDDED_SOUFFLE__
#include "souffle/CompiledOptions.h"
int main(int argc, char** argv)
{
try{
souffle::CmdOptions opt(R"(naive.dl)",
R"()",
R"()",
false,
R"()",
1);
if (!opt.parse(argc,argv)) return 1;
souffle::Sf_naive obj;
#if defined(_OPENMP) 
obj.setNumThreads(opt.getNumJobs());

#endif
obj.runAll(opt.getInputFileDir(), opt.getOutputFileDir());
return 0;
} catch(std::exception &e) { souffle::SignalHandler::instance()->error(e.what());}
}
#endif

namespace souffle {
class factory_Sf_naive: souffle::ProgramFactory {
public:
SouffleProgram* newInstance();
 factory_Sf_naive();
private:
};
} // namespace souffle
namespace souffle {
SouffleProgram* factory_Sf_naive::newInstance(){
return new Sf_naive();
}

 factory_Sf_naive::factory_Sf_naive():
ProgramFactory("naive"){
}

} // namespace souffle
namespace souffle {

#ifdef __EMBEDDED_SOUFFLE__
extern "C" {
factory_Sf_naive __factory_Sf_naive_instance;
}
#endif
} // namespace souffle

