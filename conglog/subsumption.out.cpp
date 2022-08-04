#include "souffle/CompiledSouffle.h"
#include "souffle/SignalHandler.h"
#include "souffle/SouffleInterface.h"
#include "souffle/datastructure/BTree.h"
#include "souffle/datastructure/BTreeDelete.h"
#include "souffle/datastructure/EqRel.h"
#include "souffle/io/IOSystem.h"
#include "souffle/profile/Logger.h"
#include "souffle/profile/ProfileEvent.h"
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
namespace souffle::t_btree_delete_iii__0_1_2__100__110__111 {
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
using t_ind_0 = btree_delete_set<t_tuple,t_comparator_0>;
t_ind_0 ind_0;
using iterator = t_ind_0::iterator;
struct context {
t_ind_0::operation_hints hints_0_lower;
t_ind_0::operation_hints hints_0_upper;
};
context createContext() { return context(); }
bool erase(const t_tuple& t);
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
} // namespace souffle::t_btree_delete_iii__0_1_2__100__110__111 
namespace souffle::t_btree_delete_iii__0_1_2__100__110__111 {
using t_ind_0 = Type::t_ind_0;
using iterator = Type::iterator;
using context = Type::context;
bool Type::erase(const t_tuple& t) {
if (ind_0.erase(t) > 0) {
return true;
} else return false;
}
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
} // namespace souffle::t_btree_delete_iii__0_1_2__100__110__111 
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
namespace souffle::t_btree_delete_ii__0_1__11__12__10 {
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
using t_ind_0 = btree_delete_set<t_tuple,t_comparator_0>;
t_ind_0 ind_0;
using iterator = t_ind_0::iterator;
struct context {
t_ind_0::operation_hints hints_0_lower;
t_ind_0::operation_hints hints_0_upper;
};
context createContext() { return context(); }
bool erase(const t_tuple& t);
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
range<t_ind_0::iterator> lowerUpperRange_12(const t_tuple& lower, const t_tuple& upper, context& h) const;
range<t_ind_0::iterator> lowerUpperRange_12(const t_tuple& lower, const t_tuple& upper) const;
range<t_ind_0::iterator> lowerUpperRange_10(const t_tuple& lower, const t_tuple& upper, context& h) const;
range<t_ind_0::iterator> lowerUpperRange_10(const t_tuple& lower, const t_tuple& upper) const;
bool empty() const;
std::vector<range<iterator>> partition() const;
void purge();
iterator begin() const;
iterator end() const;
void printStatistics(std::ostream& o) const;
};
} // namespace souffle::t_btree_delete_ii__0_1__11__12__10 
namespace souffle::t_btree_delete_ii__0_1__11__12__10 {
using t_ind_0 = Type::t_ind_0;
using iterator = Type::iterator;
using context = Type::context;
bool Type::erase(const t_tuple& t) {
if (ind_0.erase(t) > 0) {
return true;
} else return false;
}
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
range<t_ind_0::iterator> Type::lowerUpperRange_12(const t_tuple& lower, const t_tuple& upper, context& h) const {
t_comparator_0 comparator;
int cmp = comparator(lower, upper);
if (cmp > 0) {
    return make_range(ind_0.end(), ind_0.end());
}
return make_range(ind_0.lower_bound(lower, h.hints_0_lower), ind_0.upper_bound(upper, h.hints_0_upper));
}
range<t_ind_0::iterator> Type::lowerUpperRange_12(const t_tuple& lower, const t_tuple& upper) const {
context h;
return lowerUpperRange_12(lower,upper,h);
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
} // namespace souffle::t_btree_delete_ii__0_1__11__12__10 
namespace souffle::t_btree_ii__0_1__11__12__10 {
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
range<t_ind_0::iterator> lowerUpperRange_12(const t_tuple& lower, const t_tuple& upper, context& h) const;
range<t_ind_0::iterator> lowerUpperRange_12(const t_tuple& lower, const t_tuple& upper) const;
range<t_ind_0::iterator> lowerUpperRange_10(const t_tuple& lower, const t_tuple& upper, context& h) const;
range<t_ind_0::iterator> lowerUpperRange_10(const t_tuple& lower, const t_tuple& upper) const;
bool empty() const;
std::vector<range<iterator>> partition() const;
void purge();
iterator begin() const;
iterator end() const;
void printStatistics(std::ostream& o) const;
};
} // namespace souffle::t_btree_ii__0_1__11__12__10 
namespace souffle::t_btree_ii__0_1__11__12__10 {
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
range<t_ind_0::iterator> Type::lowerUpperRange_12(const t_tuple& lower, const t_tuple& upper, context& h) const {
t_comparator_0 comparator;
int cmp = comparator(lower, upper);
if (cmp > 0) {
    return make_range(ind_0.end(), ind_0.end());
}
return make_range(ind_0.lower_bound(lower, h.hints_0_lower), ind_0.upper_bound(upper, h.hints_0_upper));
}
range<t_ind_0::iterator> Type::lowerUpperRange_12(const t_tuple& lower, const t_tuple& upper) const {
context h;
return lowerUpperRange_12(lower,upper,h);
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
} // namespace souffle::t_btree_ii__0_1__11__12__10 
namespace souffle::t_btree_ii__0_1__11__12 {
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
range<t_ind_0::iterator> lowerUpperRange_12(const t_tuple& lower, const t_tuple& upper, context& h) const;
range<t_ind_0::iterator> lowerUpperRange_12(const t_tuple& lower, const t_tuple& upper) const;
bool empty() const;
std::vector<range<iterator>> partition() const;
void purge();
iterator begin() const;
iterator end() const;
void printStatistics(std::ostream& o) const;
};
} // namespace souffle::t_btree_ii__0_1__11__12 
namespace souffle::t_btree_ii__0_1__11__12 {
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
range<t_ind_0::iterator> Type::lowerUpperRange_12(const t_tuple& lower, const t_tuple& upper, context& h) const {
t_comparator_0 comparator;
int cmp = comparator(lower, upper);
if (cmp > 0) {
    return make_range(ind_0.end(), ind_0.end());
}
return make_range(ind_0.lower_bound(lower, h.hints_0_lower), ind_0.upper_bound(upper, h.hints_0_upper));
}
range<t_ind_0::iterator> Type::lowerUpperRange_12(const t_tuple& lower, const t_tuple& upper) const {
context h;
return lowerUpperRange_12(lower,upper,h);
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
} // namespace souffle::t_btree_ii__0_1__11__12 
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
namespace souffle::t_btree_delete_ii__0_1__11__10 {
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
using t_ind_0 = btree_delete_set<t_tuple,t_comparator_0>;
t_ind_0 ind_0;
using iterator = t_ind_0::iterator;
struct context {
t_ind_0::operation_hints hints_0_lower;
t_ind_0::operation_hints hints_0_upper;
};
context createContext() { return context(); }
bool erase(const t_tuple& t);
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
} // namespace souffle::t_btree_delete_ii__0_1__11__10 
namespace souffle::t_btree_delete_ii__0_1__11__10 {
using t_ind_0 = Type::t_ind_0;
using iterator = Type::iterator;
using context = Type::context;
bool Type::erase(const t_tuple& t) {
if (ind_0.erase(t) > 0) {
return true;
} else return false;
}
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
} // namespace souffle::t_btree_delete_ii__0_1__11__10 
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
{
	Logger logger(R"_(@t-relation-loadtime;N;subsumption.dl [1:7-1:8];loadtime;)_",iter, [&](){return rel_N_913bf6e156bb077c->size();});
if (performIO) {
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","n"},{"auxArity","0"},{"fact-dir","."},{"filename","N.in"},{"name","N"},{"operation","input"},{"params","{\"records\": {}, \"relation\": {\"arity\": 1, \"params\": [\"n\"]}}"},{"types","{\"ADTs\": {\"+:Id\": {\"arity\": 2, \"branches\": [{\"name\": \"Add\", \"types\": [\"+:Id\", \"+:Id\"]}, {\"name\": \"Var\", \"types\": [\"i:number\"]}], \"enum\": false}}, \"records\": {}, \"relation\": {\"arity\": 1, \"types\": [\"i:number\"]}}"}});
if (!inputDirectory.empty()) {directiveMap["fact-dir"] = inputDirectory;}
IOSystem::getInstance().getReader(directiveMap, symTable, recordTable)->readAll(*rel_N_913bf6e156bb077c);
} catch (std::exception& e) {std::cerr << "Error loading N data: " << e.what() << '\n';}
}
}
ProfileEventSingleton::instance().makeQuantityEvent( R"(@n-nonrecursive-relation;N;subsumption.dl [1:7-1:8];)",rel_N_913bf6e156bb077c->size(),iter);}

} // namespace souffle

namespace souffle {
class Stratum_add_ed981d530a6b23bd {
public:
 Stratum_add_ed981d530a6b23bd(SymbolTable& symTable,RecordTable& recordTable,bool& pruneImdtRels,bool& performIO,SignalHandler*& signalHandler,std::atomic<std::size_t>& iter,std::atomic<RamDomain>& ctr,std::string& inputDirectory,std::string& outputDirectory,t_btree_iii__0_1_2__111::Type& rel_delete_add_6fd868847292dbea,t_btree_ii__0_1__11::Type& rel_delete_leader_c04a5d036082e503,t_btree_ii__0_1__11::Type& rel_delete_var_73e06489152dbaa5,t_btree_iii__0_1_2__100__110__111::Type& rel_delta_add_241d705dc2fb23df,t_eqrel& rel_delta_eql_fdc75db4daac3372,t_btree_ii__0_1__11__12__10::Type& rel_delta_leader_d4159f531d436f83,t_btree_ii__0_1__11__10::Type& rel_delta_var_789565ec55b51a31,t_btree_iii__0_1_2__111::Type& rel_new_add_954a8c50e586f068,t_eqrel& rel_new_eql_10ebb01129546352,t_btree_ii__0_1__11__12::Type& rel_new_leader_99e6be51e44547e4,t_btree_ii__0_1__11__10::Type& rel_new_var_7aacd8d7c9129d14,t_btree_iii__0_1_2__111::Type& rel_reject_add_d8fb12f9ecd20122,t_btree_ii__0_1__11::Type& rel_reject_leader_c121991f9eab43a8,t_btree_ii__0_1__11::Type& rel_reject_var_3661e6768640ec8b,t_btree_i__0__2__1::Type& rel_N_913bf6e156bb077c,t_btree_delete_iii__0_1_2__100__110__111::Type& rel_add_48c57da858454f79,t_btree_iii__0_1_2__111::Type& rel_add_prep_e8dfec160429ed9e,t_eqrel& rel_eql_e1be027843ac9bc5,t_btree_delete_ii__0_1__11__12__10::Type& rel_leader_d565398e1ef92697,t_btree_delete_ii__0_1__11__10::Type& rel_var_09870be8e1a4a08e);
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
t_btree_iii__0_1_2__111::Type* rel_delete_add_6fd868847292dbea;
t_btree_ii__0_1__11::Type* rel_delete_leader_c04a5d036082e503;
t_btree_ii__0_1__11::Type* rel_delete_var_73e06489152dbaa5;
t_btree_iii__0_1_2__100__110__111::Type* rel_delta_add_241d705dc2fb23df;
t_eqrel* rel_delta_eql_fdc75db4daac3372;
t_btree_ii__0_1__11__12__10::Type* rel_delta_leader_d4159f531d436f83;
t_btree_ii__0_1__11__10::Type* rel_delta_var_789565ec55b51a31;
t_btree_iii__0_1_2__111::Type* rel_new_add_954a8c50e586f068;
t_eqrel* rel_new_eql_10ebb01129546352;
t_btree_ii__0_1__11__12::Type* rel_new_leader_99e6be51e44547e4;
t_btree_ii__0_1__11__10::Type* rel_new_var_7aacd8d7c9129d14;
t_btree_iii__0_1_2__111::Type* rel_reject_add_d8fb12f9ecd20122;
t_btree_ii__0_1__11::Type* rel_reject_leader_c121991f9eab43a8;
t_btree_ii__0_1__11::Type* rel_reject_var_3661e6768640ec8b;
t_btree_i__0__2__1::Type* rel_N_913bf6e156bb077c;
t_btree_delete_iii__0_1_2__100__110__111::Type* rel_add_48c57da858454f79;
t_btree_iii__0_1_2__111::Type* rel_add_prep_e8dfec160429ed9e;
t_eqrel* rel_eql_e1be027843ac9bc5;
t_btree_delete_ii__0_1__11__12__10::Type* rel_leader_d565398e1ef92697;
t_btree_delete_ii__0_1__11__10::Type* rel_var_09870be8e1a4a08e;
};
} // namespace souffle
namespace souffle {
 Stratum_add_ed981d530a6b23bd::Stratum_add_ed981d530a6b23bd(SymbolTable& symTable,RecordTable& recordTable,bool& pruneImdtRels,bool& performIO,SignalHandler*& signalHandler,std::atomic<std::size_t>& iter,std::atomic<RamDomain>& ctr,std::string& inputDirectory,std::string& outputDirectory,t_btree_iii__0_1_2__111::Type& rel_delete_add_6fd868847292dbea,t_btree_ii__0_1__11::Type& rel_delete_leader_c04a5d036082e503,t_btree_ii__0_1__11::Type& rel_delete_var_73e06489152dbaa5,t_btree_iii__0_1_2__100__110__111::Type& rel_delta_add_241d705dc2fb23df,t_eqrel& rel_delta_eql_fdc75db4daac3372,t_btree_ii__0_1__11__12__10::Type& rel_delta_leader_d4159f531d436f83,t_btree_ii__0_1__11__10::Type& rel_delta_var_789565ec55b51a31,t_btree_iii__0_1_2__111::Type& rel_new_add_954a8c50e586f068,t_eqrel& rel_new_eql_10ebb01129546352,t_btree_ii__0_1__11__12::Type& rel_new_leader_99e6be51e44547e4,t_btree_ii__0_1__11__10::Type& rel_new_var_7aacd8d7c9129d14,t_btree_iii__0_1_2__111::Type& rel_reject_add_d8fb12f9ecd20122,t_btree_ii__0_1__11::Type& rel_reject_leader_c121991f9eab43a8,t_btree_ii__0_1__11::Type& rel_reject_var_3661e6768640ec8b,t_btree_i__0__2__1::Type& rel_N_913bf6e156bb077c,t_btree_delete_iii__0_1_2__100__110__111::Type& rel_add_48c57da858454f79,t_btree_iii__0_1_2__111::Type& rel_add_prep_e8dfec160429ed9e,t_eqrel& rel_eql_e1be027843ac9bc5,t_btree_delete_ii__0_1__11__12__10::Type& rel_leader_d565398e1ef92697,t_btree_delete_ii__0_1__11__10::Type& rel_var_09870be8e1a4a08e):
symTable(symTable),
recordTable(recordTable),
pruneImdtRels(pruneImdtRels),
performIO(performIO),
signalHandler(signalHandler),
iter(iter),
ctr(ctr),
inputDirectory(inputDirectory),
outputDirectory(outputDirectory),
rel_delete_add_6fd868847292dbea(&rel_delete_add_6fd868847292dbea),
rel_delete_leader_c04a5d036082e503(&rel_delete_leader_c04a5d036082e503),
rel_delete_var_73e06489152dbaa5(&rel_delete_var_73e06489152dbaa5),
rel_delta_add_241d705dc2fb23df(&rel_delta_add_241d705dc2fb23df),
rel_delta_eql_fdc75db4daac3372(&rel_delta_eql_fdc75db4daac3372),
rel_delta_leader_d4159f531d436f83(&rel_delta_leader_d4159f531d436f83),
rel_delta_var_789565ec55b51a31(&rel_delta_var_789565ec55b51a31),
rel_new_add_954a8c50e586f068(&rel_new_add_954a8c50e586f068),
rel_new_eql_10ebb01129546352(&rel_new_eql_10ebb01129546352),
rel_new_leader_99e6be51e44547e4(&rel_new_leader_99e6be51e44547e4),
rel_new_var_7aacd8d7c9129d14(&rel_new_var_7aacd8d7c9129d14),
rel_reject_add_d8fb12f9ecd20122(&rel_reject_add_d8fb12f9ecd20122),
rel_reject_leader_c121991f9eab43a8(&rel_reject_leader_c121991f9eab43a8),
rel_reject_var_3661e6768640ec8b(&rel_reject_var_3661e6768640ec8b),
rel_N_913bf6e156bb077c(&rel_N_913bf6e156bb077c),
rel_add_48c57da858454f79(&rel_add_48c57da858454f79),
rel_add_prep_e8dfec160429ed9e(&rel_add_prep_e8dfec160429ed9e),
rel_eql_e1be027843ac9bc5(&rel_eql_e1be027843ac9bc5),
rel_leader_d565398e1ef92697(&rel_leader_d565398e1ef92697),
rel_var_09870be8e1a4a08e(&rel_var_09870be8e1a4a08e){
}

void Stratum_add_ed981d530a6b23bd::run([[maybe_unused]] const std::vector<RamDomain>& args,[[maybe_unused]] std::vector<RamDomain>& ret){
{
	Logger logger(R"_(@t-nonrecursive-relation;add;subsumption.dl [8:7-8:10];)_",iter, [&](){return rel_add_48c57da858454f79->size();});
signalHandler->setMsg(R"_(add(x,y,c) :- 
   add_prep(x,y,c).
in file subsumption.dl [21:1-21:35])_");
{
	Logger logger(R"_(@t-nonrecursive-rule;add;subsumption.dl [21:1-21:35];add(x,y,c) :- \n   add_prep(x,y,c).;)_",iter, [&](){return rel_add_48c57da858454f79->size();});
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
}
}
ProfileEventSingleton::instance().makeQuantityEvent( R"(@n-nonrecursive-relation;eql;subsumption.dl [7:7-7:10];)",rel_eql_e1be027843ac9bc5->size(),iter);ProfileEventSingleton::instance().makeQuantityEvent( R"(@n-nonrecursive-relation;leader;subsumption.dl [57:7-57:13];)",rel_leader_d565398e1ef92697->size(),iter);{
	Logger logger(R"_(@t-nonrecursive-relation;var;subsumption.dl [9:7-9:10];)_",iter, [&](){return rel_var_09870be8e1a4a08e->size();});
signalHandler->setMsg(R"_(var(1,$Var(1)).
in file subsumption.dl [12:1-12:17])_");
{
	Logger logger(R"_(@t-nonrecursive-rule;var;subsumption.dl [12:1-12:17];var(1,$Var(1)).;)_",iter, [&](){return rel_var_09870be8e1a4a08e->size();});
[&](){
CREATE_OP_CONTEXT(rel_var_09870be8e1a4a08e_op_ctxt,rel_var_09870be8e1a4a08e->createContext());
Tuple<RamDomain,2> tuple{{ramBitCast(RamSigned(1)),ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(RamSigned(1))),ramBitCast(ramBitCast(RamSigned(1)))}}
))}};
rel_var_09870be8e1a4a08e->insert(tuple,READ_OP_CONTEXT(rel_var_09870be8e1a4a08e_op_ctxt));
}
();}
signalHandler->setMsg(R"_(var(2,$Var(2)).
in file subsumption.dl [13:1-13:17])_");
{
	Logger logger(R"_(@t-nonrecursive-rule;var;subsumption.dl [13:1-13:17];var(2,$Var(2)).;)_",iter, [&](){return rel_var_09870be8e1a4a08e->size();});
[&](){
CREATE_OP_CONTEXT(rel_var_09870be8e1a4a08e_op_ctxt,rel_var_09870be8e1a4a08e->createContext());
Tuple<RamDomain,2> tuple{{ramBitCast(RamSigned(2)),ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(RamSigned(1))),ramBitCast(ramBitCast(RamSigned(2)))}}
))}};
rel_var_09870be8e1a4a08e->insert(tuple,READ_OP_CONTEXT(rel_var_09870be8e1a4a08e_op_ctxt));
}
();}
signalHandler->setMsg(R"_(var((x+1),$Var((x+1))) :- 
   add_prep($Var(x),_,_),
   x <= n,
   N(n).
in file subsumption.dl [15:1-19:15])_");
{
	Logger logger(R"_(@t-nonrecursive-rule;var;subsumption.dl [15:1-19:15];var((x+1),$Var((x+1))) :- \n   add_prep($Var(x),_,_),\n   x <= n,\n   N(n).;)_",iter, [&](){return rel_var_09870be8e1a4a08e->size();});
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
}
}
signalHandler->setMsg(R"_(add(x1,y1,c1) <= add(x2,y2,c2) :- 
   leader(x1,x2),
   leader(y1,y2),
   leader(c1,c2). .plan 0:(1,3,4,5,2), 1:(1,3,4,5,2), 2:(1,3,4,5,2), 3:(1,3,4,5,2), 4:(1,3,4,5,2), 5:(1,3,4,5,2)
in file subsumption.dl [50:1-52:123])_");
{
	Logger logger(R"_(@t-nonrecursive-rule;add;subsumption.dl [50:1-52:123];add(x1,y1,c1) <= add(x2,y2,c2) :- \n   leader(x1,x2),\n   leader(y1,y2),\n   leader(c1,c2). .plan 0:(1,3,4,5,2), 1:(1,3,4,5,2), 2:(1,3,4,5,2), 3:(1,3,4,5,2), 4:(1,3,4,5,2), 5:(1,3,4,5,2);)_",iter, [&](){return rel_add_48c57da858454f79->size();});
if(!(rel_add_48c57da858454f79->empty()) && !(rel_leader_d565398e1ef92697->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_delete_add_6fd868847292dbea_op_ctxt,rel_delete_add_6fd868847292dbea->createContext());
CREATE_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt,rel_add_48c57da858454f79->createContext());
CREATE_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt,rel_leader_d565398e1ef92697->createContext());
for(const auto& env0 : *rel_add_48c57da858454f79) {
auto range = rel_leader_d565398e1ef92697->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt));
for(const auto& env1 : range) {
auto range = rel_leader_d565398e1ef92697->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt));
for(const auto& env2 : range) {
auto range = rel_leader_d565398e1ef92697->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[2]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[2]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt));
for(const auto& env3 : range) {
if( !((ramBitCast<RamDomain>(env0[2]) == ramBitCast<RamDomain>(env3[1])) && (ramBitCast<RamDomain>(env0[0]) == ramBitCast<RamDomain>(env1[1])) && (ramBitCast<RamDomain>(env0[1]) == ramBitCast<RamDomain>(env2[1]))) && rel_add_48c57da858454f79->contains(Tuple<RamDomain,3>{{ramBitCast(env1[1]),ramBitCast(env2[1]),ramBitCast(env3[1])}},READ_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt))) {
Tuple<RamDomain,3> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1]),ramBitCast(env0[2])}};
rel_delete_add_6fd868847292dbea->insert(tuple,READ_OP_CONTEXT(rel_delete_add_6fd868847292dbea_op_ctxt));
}
}
}
}
}
}
();}
}
[&](){
CREATE_OP_CONTEXT(rel_delete_add_6fd868847292dbea_op_ctxt,rel_delete_add_6fd868847292dbea->createContext());
for(const auto& env0 : *rel_delete_add_6fd868847292dbea) {
Tuple<RamDomain,3> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1]),ramBitCast(env0[2])}};
rel_add_48c57da858454f79->erase(tuple);
}
}
();rel_delete_add_6fd868847292dbea->purge();
signalHandler->setMsg(R"_(leader(x,y1) <= leader(x,y2) :- 
   as(y1, number) <= as(y2, number).
in file subsumption.dl [59:1-60:38])_");
{
	Logger logger(R"_(@t-nonrecursive-rule;leader;subsumption.dl [59:1-60:38];leader(x,y1) <= leader(x,y2) :- \n   as(y1, number) <= as(y2, number).;)_",iter, [&](){return rel_leader_d565398e1ef92697->size();});
if(!(rel_leader_d565398e1ef92697->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_delete_leader_c04a5d036082e503_op_ctxt,rel_delete_leader_c04a5d036082e503->createContext());
CREATE_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt,rel_leader_d565398e1ef92697->createContext());
for(const auto& env0 : *rel_leader_d565398e1ef92697) {
auto range = rel_leader_d565398e1ef92697->lowerUpperRange_12(Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast(env0[1])}},Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt));
for(const auto& env1 : range) {
if( !((ramBitCast<RamDomain>(env0[1]) == ramBitCast<RamDomain>(env1[1])))) {
Tuple<RamDomain,2> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1])}};
rel_delete_leader_c04a5d036082e503->insert(tuple,READ_OP_CONTEXT(rel_delete_leader_c04a5d036082e503_op_ctxt));
break;
}
}
}
}
();}
}
[&](){
CREATE_OP_CONTEXT(rel_delete_leader_c04a5d036082e503_op_ctxt,rel_delete_leader_c04a5d036082e503->createContext());
for(const auto& env0 : *rel_delete_leader_c04a5d036082e503) {
Tuple<RamDomain,2> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1])}};
rel_leader_d565398e1ef92697->erase(tuple);
}
}
();rel_delete_leader_c04a5d036082e503->purge();
signalHandler->setMsg(R"_(var(x,c1) <= var(x,c2) :- 
   leader(c1,c2).
in file subsumption.dl [53:1-54:20])_");
{
	Logger logger(R"_(@t-nonrecursive-rule;var;subsumption.dl [53:1-54:20];var(x,c1) <= var(x,c2) :- \n   leader(c1,c2).;)_",iter, [&](){return rel_var_09870be8e1a4a08e->size();});
if(!(rel_leader_d565398e1ef92697->empty()) && !(rel_var_09870be8e1a4a08e->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_delete_var_73e06489152dbaa5_op_ctxt,rel_delete_var_73e06489152dbaa5->createContext());
CREATE_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt,rel_leader_d565398e1ef92697->createContext());
CREATE_OP_CONTEXT(rel_var_09870be8e1a4a08e_op_ctxt,rel_var_09870be8e1a4a08e->createContext());
for(const auto& env0 : *rel_var_09870be8e1a4a08e) {
auto range = rel_var_09870be8e1a4a08e->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_var_09870be8e1a4a08e_op_ctxt));
for(const auto& env1 : range) {
if( !((ramBitCast<RamDomain>(env0[1]) == ramBitCast<RamDomain>(env1[1]))) && rel_leader_d565398e1ef92697->contains(Tuple<RamDomain,2>{{ramBitCast(env0[1]),ramBitCast(env1[1])}},READ_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt))) {
Tuple<RamDomain,2> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1])}};
rel_delete_var_73e06489152dbaa5->insert(tuple,READ_OP_CONTEXT(rel_delete_var_73e06489152dbaa5_op_ctxt));
}
}
}
}
();}
}
[&](){
CREATE_OP_CONTEXT(rel_delete_var_73e06489152dbaa5_op_ctxt,rel_delete_var_73e06489152dbaa5->createContext());
for(const auto& env0 : *rel_delete_var_73e06489152dbaa5) {
Tuple<RamDomain,2> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1])}};
rel_var_09870be8e1a4a08e->erase(tuple);
}
}
();rel_delete_var_73e06489152dbaa5->purge();
[&](){
CREATE_OP_CONTEXT(rel_delta_add_241d705dc2fb23df_op_ctxt,rel_delta_add_241d705dc2fb23df->createContext());
CREATE_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt,rel_add_48c57da858454f79->createContext());
for(const auto& env0 : *rel_add_48c57da858454f79) {
Tuple<RamDomain,3> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1]),ramBitCast(env0[2])}};
rel_delta_add_241d705dc2fb23df->insert(tuple,READ_OP_CONTEXT(rel_delta_add_241d705dc2fb23df_op_ctxt));
}
}
();rel_eql_e1be027843ac9bc5->extendAndInsert(*rel_delta_eql_fdc75db4daac3372);
[&](){
CREATE_OP_CONTEXT(rel_delta_leader_d4159f531d436f83_op_ctxt,rel_delta_leader_d4159f531d436f83->createContext());
CREATE_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt,rel_leader_d565398e1ef92697->createContext());
for(const auto& env0 : *rel_leader_d565398e1ef92697) {
Tuple<RamDomain,2> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1])}};
rel_delta_leader_d4159f531d436f83->insert(tuple,READ_OP_CONTEXT(rel_delta_leader_d4159f531d436f83_op_ctxt));
}
}
();[&](){
CREATE_OP_CONTEXT(rel_delta_var_789565ec55b51a31_op_ctxt,rel_delta_var_789565ec55b51a31->createContext());
CREATE_OP_CONTEXT(rel_var_09870be8e1a4a08e_op_ctxt,rel_var_09870be8e1a4a08e->createContext());
for(const auto& env0 : *rel_var_09870be8e1a4a08e) {
Tuple<RamDomain,2> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1])}};
rel_delta_var_789565ec55b51a31->insert(tuple,READ_OP_CONTEXT(rel_delta_var_789565ec55b51a31_op_ctxt));
}
}
();iter = 0;
for(;;) {
{
	Logger logger(R"_(@t-recursive-relation;add;subsumption.dl [8:7-8:10];)_",iter, [&](){return rel_new_add_954a8c50e586f068->size();});
signalHandler->setMsg(R"_(add(x1,y1,c1) :- 
   add(x,y,c),
   leader(x,x1),
   leader(y,y1),
   leader(c,c1).
in file subsumption.dl [47:1-47:78])_");
{
	Logger logger(R"_(@t-recursive-rule;add;0;subsumption.dl [47:1-47:78];add(x1,y1,c1) :- \n   add(x,y,c),\n   leader(x,x1),\n   leader(y,y1),\n   leader(c,c1).;)_",iter, [&](){return rel_new_add_954a8c50e586f068->size();});
if(!(rel_leader_d565398e1ef92697->empty()) && !(rel_delta_add_241d705dc2fb23df->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_delta_add_241d705dc2fb23df_op_ctxt,rel_delta_add_241d705dc2fb23df->createContext());
CREATE_OP_CONTEXT(rel_delta_leader_d4159f531d436f83_op_ctxt,rel_delta_leader_d4159f531d436f83->createContext());
CREATE_OP_CONTEXT(rel_new_add_954a8c50e586f068_op_ctxt,rel_new_add_954a8c50e586f068->createContext());
CREATE_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt,rel_add_48c57da858454f79->createContext());
CREATE_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt,rel_leader_d565398e1ef92697->createContext());
for(const auto& env0 : *rel_delta_add_241d705dc2fb23df) {
auto range = rel_leader_d565398e1ef92697->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt));
for(const auto& env1 : range) {
if( !(rel_delta_leader_d4159f531d436f83->contains(Tuple<RamDomain,2>{{ramBitCast(env0[0]),ramBitCast(env1[1])}},READ_OP_CONTEXT(rel_delta_leader_d4159f531d436f83_op_ctxt)))) {
auto range = rel_leader_d565398e1ef92697->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt));
for(const auto& env2 : range) {
if( !(rel_delta_leader_d4159f531d436f83->contains(Tuple<RamDomain,2>{{ramBitCast(env0[1]),ramBitCast(env2[1])}},READ_OP_CONTEXT(rel_delta_leader_d4159f531d436f83_op_ctxt)))) {
auto range = rel_leader_d565398e1ef92697->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[2]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[2]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt));
for(const auto& env3 : range) {
if( !(rel_delta_leader_d4159f531d436f83->contains(Tuple<RamDomain,2>{{ramBitCast(env0[2]),ramBitCast(env3[1])}},READ_OP_CONTEXT(rel_delta_leader_d4159f531d436f83_op_ctxt))) && !(rel_add_48c57da858454f79->contains(Tuple<RamDomain,3>{{ramBitCast(env1[1]),ramBitCast(env2[1]),ramBitCast(env3[1])}},READ_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt)))) {
Tuple<RamDomain,3> tuple{{ramBitCast(env1[1]),ramBitCast(env2[1]),ramBitCast(env3[1])}};
rel_new_add_954a8c50e586f068->insert(tuple,READ_OP_CONTEXT(rel_new_add_954a8c50e586f068_op_ctxt));
}
}
}
}
}
}
}
}
();}
}
signalHandler->setMsg(R"_(add(x1,y1,c1) :- 
   add(x,y,c),
   leader(x,x1),
   leader(y,y1),
   leader(c,c1).
in file subsumption.dl [47:1-47:78])_");
{
	Logger logger(R"_(@t-recursive-rule;add;1;subsumption.dl [47:1-47:78];add(x1,y1,c1) :- \n   add(x,y,c),\n   leader(x,x1),\n   leader(y,y1),\n   leader(c,c1).;)_",iter, [&](){return rel_new_add_954a8c50e586f068->size();});
if(!(rel_add_48c57da858454f79->empty()) && !(rel_delta_leader_d4159f531d436f83->empty()) && !(rel_leader_d565398e1ef92697->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_delta_leader_d4159f531d436f83_op_ctxt,rel_delta_leader_d4159f531d436f83->createContext());
CREATE_OP_CONTEXT(rel_new_add_954a8c50e586f068_op_ctxt,rel_new_add_954a8c50e586f068->createContext());
CREATE_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt,rel_add_48c57da858454f79->createContext());
CREATE_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt,rel_leader_d565398e1ef92697->createContext());
for(const auto& env0 : *rel_add_48c57da858454f79) {
auto range = rel_delta_leader_d4159f531d436f83->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_delta_leader_d4159f531d436f83_op_ctxt));
for(const auto& env1 : range) {
auto range = rel_leader_d565398e1ef92697->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt));
for(const auto& env2 : range) {
if( !(rel_delta_leader_d4159f531d436f83->contains(Tuple<RamDomain,2>{{ramBitCast(env0[1]),ramBitCast(env2[1])}},READ_OP_CONTEXT(rel_delta_leader_d4159f531d436f83_op_ctxt)))) {
auto range = rel_leader_d565398e1ef92697->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[2]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[2]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt));
for(const auto& env3 : range) {
if( !(rel_add_48c57da858454f79->contains(Tuple<RamDomain,3>{{ramBitCast(env1[1]),ramBitCast(env2[1]),ramBitCast(env3[1])}},READ_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt))) && !(rel_delta_leader_d4159f531d436f83->contains(Tuple<RamDomain,2>{{ramBitCast(env0[2]),ramBitCast(env3[1])}},READ_OP_CONTEXT(rel_delta_leader_d4159f531d436f83_op_ctxt)))) {
Tuple<RamDomain,3> tuple{{ramBitCast(env1[1]),ramBitCast(env2[1]),ramBitCast(env3[1])}};
rel_new_add_954a8c50e586f068->insert(tuple,READ_OP_CONTEXT(rel_new_add_954a8c50e586f068_op_ctxt));
}
}
}
}
}
}
}
();}
}
signalHandler->setMsg(R"_(add(x1,y1,c1) :- 
   add(x,y,c),
   leader(x,x1),
   leader(y,y1),
   leader(c,c1).
in file subsumption.dl [47:1-47:78])_");
{
	Logger logger(R"_(@t-recursive-rule;add;2;subsumption.dl [47:1-47:78];add(x1,y1,c1) :- \n   add(x,y,c),\n   leader(x,x1),\n   leader(y,y1),\n   leader(c,c1).;)_",iter, [&](){return rel_new_add_954a8c50e586f068->size();});
if(!(rel_delta_leader_d4159f531d436f83->empty()) && !(rel_add_48c57da858454f79->empty()) && !(rel_leader_d565398e1ef92697->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_delta_leader_d4159f531d436f83_op_ctxt,rel_delta_leader_d4159f531d436f83->createContext());
CREATE_OP_CONTEXT(rel_new_add_954a8c50e586f068_op_ctxt,rel_new_add_954a8c50e586f068->createContext());
CREATE_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt,rel_add_48c57da858454f79->createContext());
CREATE_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt,rel_leader_d565398e1ef92697->createContext());
for(const auto& env0 : *rel_add_48c57da858454f79) {
auto range = rel_leader_d565398e1ef92697->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt));
for(const auto& env1 : range) {
auto range = rel_delta_leader_d4159f531d436f83->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_delta_leader_d4159f531d436f83_op_ctxt));
for(const auto& env2 : range) {
auto range = rel_leader_d565398e1ef92697->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[2]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[2]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt));
for(const auto& env3 : range) {
if( !(rel_add_48c57da858454f79->contains(Tuple<RamDomain,3>{{ramBitCast(env1[1]),ramBitCast(env2[1]),ramBitCast(env3[1])}},READ_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt))) && !(rel_delta_leader_d4159f531d436f83->contains(Tuple<RamDomain,2>{{ramBitCast(env0[2]),ramBitCast(env3[1])}},READ_OP_CONTEXT(rel_delta_leader_d4159f531d436f83_op_ctxt)))) {
Tuple<RamDomain,3> tuple{{ramBitCast(env1[1]),ramBitCast(env2[1]),ramBitCast(env3[1])}};
rel_new_add_954a8c50e586f068->insert(tuple,READ_OP_CONTEXT(rel_new_add_954a8c50e586f068_op_ctxt));
}
}
}
}
}
}
();}
}
signalHandler->setMsg(R"_(add(x1,y1,c1) :- 
   add(x,y,c),
   leader(x,x1),
   leader(y,y1),
   leader(c,c1).
in file subsumption.dl [47:1-47:78])_");
{
	Logger logger(R"_(@t-recursive-rule;add;3;subsumption.dl [47:1-47:78];add(x1,y1,c1) :- \n   add(x,y,c),\n   leader(x,x1),\n   leader(y,y1),\n   leader(c,c1).;)_",iter, [&](){return rel_new_add_954a8c50e586f068->size();});
if(!(rel_leader_d565398e1ef92697->empty()) && !(rel_add_48c57da858454f79->empty()) && !(rel_delta_leader_d4159f531d436f83->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_delta_leader_d4159f531d436f83_op_ctxt,rel_delta_leader_d4159f531d436f83->createContext());
CREATE_OP_CONTEXT(rel_new_add_954a8c50e586f068_op_ctxt,rel_new_add_954a8c50e586f068->createContext());
CREATE_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt,rel_add_48c57da858454f79->createContext());
CREATE_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt,rel_leader_d565398e1ef92697->createContext());
for(const auto& env0 : *rel_add_48c57da858454f79) {
auto range = rel_leader_d565398e1ef92697->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt));
for(const auto& env1 : range) {
auto range = rel_leader_d565398e1ef92697->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt));
for(const auto& env2 : range) {
auto range = rel_delta_leader_d4159f531d436f83->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[2]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[2]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_delta_leader_d4159f531d436f83_op_ctxt));
for(const auto& env3 : range) {
if( !(rel_add_48c57da858454f79->contains(Tuple<RamDomain,3>{{ramBitCast(env1[1]),ramBitCast(env2[1]),ramBitCast(env3[1])}},READ_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt)))) {
Tuple<RamDomain,3> tuple{{ramBitCast(env1[1]),ramBitCast(env2[1]),ramBitCast(env3[1])}};
rel_new_add_954a8c50e586f068->insert(tuple,READ_OP_CONTEXT(rel_new_add_954a8c50e586f068_op_ctxt));
}
}
}
}
}
}
();}
}
signalHandler->setMsg(R"_(add(x,y,$Add(x, y)) :- 
   add(y,x,_).
in file subsumption.dl [32:1-36:18])_");
{
	Logger logger(R"_(@t-recursive-rule;add;0;subsumption.dl [32:1-36:18];add(x,y,$Add(x, y)) :- \n   add(y,x,_).;)_",iter, [&](){return rel_new_add_954a8c50e586f068->size();});
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
}
signalHandler->setMsg(R"_(add(x,$Add(y, z),$Add(x, $Add(y, z))) :- 
   add(x,y,xy),
   add(xy,z,_).
in file subsumption.dl [39:1-44:38])_");
{
	Logger logger(R"_(@t-recursive-rule;add;0;subsumption.dl [39:1-44:38];add(x,$Add(y, z),$Add(x, $Add(y, z))) :- \n   add(x,y,xy),\n   add(xy,z,_).;)_",iter, [&](){return rel_new_add_954a8c50e586f068->size();});
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
}
signalHandler->setMsg(R"_(add(x,$Add(y, z),$Add(x, $Add(y, z))) :- 
   add(x,y,xy),
   add(xy,z,_).
in file subsumption.dl [39:1-44:38])_");
{
	Logger logger(R"_(@t-recursive-rule;add;1;subsumption.dl [39:1-44:38];add(x,$Add(y, z),$Add(x, $Add(y, z))) :- \n   add(x,y,xy),\n   add(xy,z,_).;)_",iter, [&](){return rel_new_add_954a8c50e586f068->size();});
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
}
signalHandler->setMsg(R"_(add(y,z,$Add(y, z)) :- 
   add(_,y,xy),
   add(xy,z,_).
in file subsumption.dl [39:1-44:38])_");
{
	Logger logger(R"_(@t-recursive-rule;add;0;subsumption.dl [39:1-44:38];add(y,z,$Add(y, z)) :- \n   add(_,y,xy),\n   add(xy,z,_).;)_",iter, [&](){return rel_new_add_954a8c50e586f068->size();});
if(!(rel_delta_add_241d705dc2fb23df->empty()) && !(rel_add_48c57da858454f79->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_delta_add_241d705dc2fb23df_op_ctxt,rel_delta_add_241d705dc2fb23df->createContext());
CREATE_OP_CONTEXT(rel_new_add_954a8c50e586f068_op_ctxt,rel_new_add_954a8c50e586f068->createContext());
CREATE_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt,rel_add_48c57da858454f79->createContext());
for(const auto& env0 : *rel_delta_add_241d705dc2fb23df) {
auto range = rel_add_48c57da858454f79->lowerUpperRange_100(Tuple<RamDomain,3>{{ramBitCast(env0[2]), ramBitCast<RamDomain>(MIN_RAM_SIGNED), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,3>{{ramBitCast(env0[2]), ramBitCast<RamDomain>(MAX_RAM_SIGNED), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt));
for(const auto& env1 : range) {
if( !(!rel_delta_add_241d705dc2fb23df->lowerUpperRange_110(Tuple<RamDomain,3>{{ramBitCast(env0[2]), ramBitCast(env1[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,3>{{ramBitCast(env0[2]), ramBitCast(env1[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_delta_add_241d705dc2fb23df_op_ctxt)).empty()) && !(rel_add_48c57da858454f79->contains(Tuple<RamDomain,3>{{ramBitCast(env0[1]),ramBitCast(env1[1]),ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(RamSigned(0))),ramBitCast(ramBitCast(pack(recordTable,Tuple<RamDomain,2>{{ramBitCast(ramBitCast(env0[1])),ramBitCast(ramBitCast(env1[1]))}}
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
}
signalHandler->setMsg(R"_(add(y,z,$Add(y, z)) :- 
   add(_,y,xy),
   add(xy,z,_).
in file subsumption.dl [39:1-44:38])_");
{
	Logger logger(R"_(@t-recursive-rule;add;1;subsumption.dl [39:1-44:38];add(y,z,$Add(y, z)) :- \n   add(_,y,xy),\n   add(xy,z,_).;)_",iter, [&](){return rel_new_add_954a8c50e586f068->size();});
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
}
}
{
	Logger logger(R"_(@t-recursive-relation;eql;subsumption.dl [7:7-7:10];)_",iter, [&](){return rel_new_eql_10ebb01129546352->size();});
signalHandler->setMsg(R"_(eql(x,x) :- 
   var(_,x).
in file subsumption.dl [24:1-24:24])_");
{
	Logger logger(R"_(@t-recursive-rule;eql;0;subsumption.dl [24:1-24:24];eql(x,x) :- \n   var(_,x).;)_",iter, [&](){return rel_new_eql_10ebb01129546352->size();});
if(!(rel_delta_var_789565ec55b51a31->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_delta_var_789565ec55b51a31_op_ctxt,rel_delta_var_789565ec55b51a31->createContext());
CREATE_OP_CONTEXT(rel_new_eql_10ebb01129546352_op_ctxt,rel_new_eql_10ebb01129546352->createContext());
CREATE_OP_CONTEXT(rel_eql_e1be027843ac9bc5_op_ctxt,rel_eql_e1be027843ac9bc5->createContext());
for(const auto& env0 : *rel_delta_var_789565ec55b51a31) {
if( !(rel_eql_e1be027843ac9bc5->contains(Tuple<RamDomain,2>{{ramBitCast(env0[1]),ramBitCast(env0[1])}},READ_OP_CONTEXT(rel_eql_e1be027843ac9bc5_op_ctxt)))) {
Tuple<RamDomain,2> tuple{{ramBitCast(env0[1]),ramBitCast(env0[1])}};
rel_new_eql_10ebb01129546352->insert(tuple,READ_OP_CONTEXT(rel_new_eql_10ebb01129546352_op_ctxt));
}
}
}
();}
}
signalHandler->setMsg(R"_(eql(x,x) :- 
   add(_,_,x).
in file subsumption.dl [25:1-25:27])_");
{
	Logger logger(R"_(@t-recursive-rule;eql;0;subsumption.dl [25:1-25:27];eql(x,x) :- \n   add(_,_,x).;)_",iter, [&](){return rel_new_eql_10ebb01129546352->size();});
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
}
signalHandler->setMsg(R"_(eql(c1,c2) :- 
   add(x,y,c1),
   add(x,y,c2),
   c1 != c2.
in file subsumption.dl [28:1-28:55])_");
{
	Logger logger(R"_(@t-recursive-rule;eql;0;subsumption.dl [28:1-28:55];eql(c1,c2) :- \n   add(x,y,c1),\n   add(x,y,c2),\n   c1 != c2.;)_",iter, [&](){return rel_new_eql_10ebb01129546352->size();});
if(!(rel_delta_add_241d705dc2fb23df->empty()) && !(rel_add_48c57da858454f79->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_delta_add_241d705dc2fb23df_op_ctxt,rel_delta_add_241d705dc2fb23df->createContext());
CREATE_OP_CONTEXT(rel_new_eql_10ebb01129546352_op_ctxt,rel_new_eql_10ebb01129546352->createContext());
CREATE_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt,rel_add_48c57da858454f79->createContext());
CREATE_OP_CONTEXT(rel_eql_e1be027843ac9bc5_op_ctxt,rel_eql_e1be027843ac9bc5->createContext());
for(const auto& env0 : *rel_delta_add_241d705dc2fb23df) {
auto range = rel_add_48c57da858454f79->lowerUpperRange_110(Tuple<RamDomain,3>{{ramBitCast(env0[0]), ramBitCast(env0[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,3>{{ramBitCast(env0[0]), ramBitCast(env0[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt));
for(const auto& env1 : range) {
if( (ramBitCast<RamDomain>(env0[2]) != ramBitCast<RamDomain>(env1[2])) && !(rel_delta_add_241d705dc2fb23df->contains(Tuple<RamDomain,3>{{ramBitCast(env0[0]),ramBitCast(env0[1]),ramBitCast(env1[2])}},READ_OP_CONTEXT(rel_delta_add_241d705dc2fb23df_op_ctxt))) && !(rel_eql_e1be027843ac9bc5->contains(Tuple<RamDomain,2>{{ramBitCast(env0[2]),ramBitCast(env1[2])}},READ_OP_CONTEXT(rel_eql_e1be027843ac9bc5_op_ctxt)))) {
Tuple<RamDomain,2> tuple{{ramBitCast(env0[2]),ramBitCast(env1[2])}};
rel_new_eql_10ebb01129546352->insert(tuple,READ_OP_CONTEXT(rel_new_eql_10ebb01129546352_op_ctxt));
}
}
}
}
();}
}
signalHandler->setMsg(R"_(eql(c1,c2) :- 
   add(x,y,c1),
   add(x,y,c2),
   c1 != c2.
in file subsumption.dl [28:1-28:55])_");
{
	Logger logger(R"_(@t-recursive-rule;eql;1;subsumption.dl [28:1-28:55];eql(c1,c2) :- \n   add(x,y,c1),\n   add(x,y,c2),\n   c1 != c2.;)_",iter, [&](){return rel_new_eql_10ebb01129546352->size();});
if(!(rel_add_48c57da858454f79->empty()) && !(rel_delta_add_241d705dc2fb23df->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_delta_add_241d705dc2fb23df_op_ctxt,rel_delta_add_241d705dc2fb23df->createContext());
CREATE_OP_CONTEXT(rel_new_eql_10ebb01129546352_op_ctxt,rel_new_eql_10ebb01129546352->createContext());
CREATE_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt,rel_add_48c57da858454f79->createContext());
CREATE_OP_CONTEXT(rel_eql_e1be027843ac9bc5_op_ctxt,rel_eql_e1be027843ac9bc5->createContext());
for(const auto& env0 : *rel_add_48c57da858454f79) {
auto range = rel_delta_add_241d705dc2fb23df->lowerUpperRange_110(Tuple<RamDomain,3>{{ramBitCast(env0[0]), ramBitCast(env0[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,3>{{ramBitCast(env0[0]), ramBitCast(env0[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_delta_add_241d705dc2fb23df_op_ctxt));
for(const auto& env1 : range) {
if( (ramBitCast<RamDomain>(env0[2]) != ramBitCast<RamDomain>(env1[2])) && !(rel_eql_e1be027843ac9bc5->contains(Tuple<RamDomain,2>{{ramBitCast(env0[2]),ramBitCast(env1[2])}},READ_OP_CONTEXT(rel_eql_e1be027843ac9bc5_op_ctxt)))) {
Tuple<RamDomain,2> tuple{{ramBitCast(env0[2]),ramBitCast(env1[2])}};
rel_new_eql_10ebb01129546352->insert(tuple,READ_OP_CONTEXT(rel_new_eql_10ebb01129546352_op_ctxt));
}
}
}
}
();}
}
signalHandler->setMsg(R"_(eql(c1,c2) :- 
   var(x,c1),
   var(x,c2),
   c1 != c2.
in file subsumption.dl [29:1-29:49])_");
{
	Logger logger(R"_(@t-recursive-rule;eql;0;subsumption.dl [29:1-29:49];eql(c1,c2) :- \n   var(x,c1),\n   var(x,c2),\n   c1 != c2.;)_",iter, [&](){return rel_new_eql_10ebb01129546352->size();});
if(!(rel_delta_var_789565ec55b51a31->empty()) && !(rel_var_09870be8e1a4a08e->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_delta_var_789565ec55b51a31_op_ctxt,rel_delta_var_789565ec55b51a31->createContext());
CREATE_OP_CONTEXT(rel_new_eql_10ebb01129546352_op_ctxt,rel_new_eql_10ebb01129546352->createContext());
CREATE_OP_CONTEXT(rel_eql_e1be027843ac9bc5_op_ctxt,rel_eql_e1be027843ac9bc5->createContext());
CREATE_OP_CONTEXT(rel_var_09870be8e1a4a08e_op_ctxt,rel_var_09870be8e1a4a08e->createContext());
for(const auto& env0 : *rel_delta_var_789565ec55b51a31) {
auto range = rel_var_09870be8e1a4a08e->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_var_09870be8e1a4a08e_op_ctxt));
for(const auto& env1 : range) {
if( (ramBitCast<RamDomain>(env0[1]) != ramBitCast<RamDomain>(env1[1])) && !(rel_delta_var_789565ec55b51a31->contains(Tuple<RamDomain,2>{{ramBitCast(env0[0]),ramBitCast(env1[1])}},READ_OP_CONTEXT(rel_delta_var_789565ec55b51a31_op_ctxt))) && !(rel_eql_e1be027843ac9bc5->contains(Tuple<RamDomain,2>{{ramBitCast(env0[1]),ramBitCast(env1[1])}},READ_OP_CONTEXT(rel_eql_e1be027843ac9bc5_op_ctxt)))) {
Tuple<RamDomain,2> tuple{{ramBitCast(env0[1]),ramBitCast(env1[1])}};
rel_new_eql_10ebb01129546352->insert(tuple,READ_OP_CONTEXT(rel_new_eql_10ebb01129546352_op_ctxt));
}
}
}
}
();}
}
signalHandler->setMsg(R"_(eql(c1,c2) :- 
   var(x,c1),
   var(x,c2),
   c1 != c2.
in file subsumption.dl [29:1-29:49])_");
{
	Logger logger(R"_(@t-recursive-rule;eql;1;subsumption.dl [29:1-29:49];eql(c1,c2) :- \n   var(x,c1),\n   var(x,c2),\n   c1 != c2.;)_",iter, [&](){return rel_new_eql_10ebb01129546352->size();});
if(!(rel_var_09870be8e1a4a08e->empty()) && !(rel_delta_var_789565ec55b51a31->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_delta_var_789565ec55b51a31_op_ctxt,rel_delta_var_789565ec55b51a31->createContext());
CREATE_OP_CONTEXT(rel_new_eql_10ebb01129546352_op_ctxt,rel_new_eql_10ebb01129546352->createContext());
CREATE_OP_CONTEXT(rel_eql_e1be027843ac9bc5_op_ctxt,rel_eql_e1be027843ac9bc5->createContext());
CREATE_OP_CONTEXT(rel_var_09870be8e1a4a08e_op_ctxt,rel_var_09870be8e1a4a08e->createContext());
for(const auto& env0 : *rel_var_09870be8e1a4a08e) {
auto range = rel_delta_var_789565ec55b51a31->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_delta_var_789565ec55b51a31_op_ctxt));
for(const auto& env1 : range) {
if( (ramBitCast<RamDomain>(env0[1]) != ramBitCast<RamDomain>(env1[1])) && !(rel_eql_e1be027843ac9bc5->contains(Tuple<RamDomain,2>{{ramBitCast(env0[1]),ramBitCast(env1[1])}},READ_OP_CONTEXT(rel_eql_e1be027843ac9bc5_op_ctxt)))) {
Tuple<RamDomain,2> tuple{{ramBitCast(env0[1]),ramBitCast(env1[1])}};
rel_new_eql_10ebb01129546352->insert(tuple,READ_OP_CONTEXT(rel_new_eql_10ebb01129546352_op_ctxt));
}
}
}
}
();}
}
signalHandler->setMsg(R"_(eql($Add(x, y),yx) :- 
   add(y,x,yx).
in file subsumption.dl [32:1-36:18])_");
{
	Logger logger(R"_(@t-recursive-rule;eql;0;subsumption.dl [32:1-36:18];eql($Add(x, y),yx) :- \n   add(y,x,yx).;)_",iter, [&](){return rel_new_eql_10ebb01129546352->size();});
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
}
signalHandler->setMsg(R"_(eql(xy_z,$Add(x, $Add(y, z))) :- 
   add(x,y,xy),
   add(xy,z,xy_z).
in file subsumption.dl [39:1-44:38])_");
{
	Logger logger(R"_(@t-recursive-rule;eql;0;subsumption.dl [39:1-44:38];eql(xy_z,$Add(x, $Add(y, z))) :- \n   add(x,y,xy),\n   add(xy,z,xy_z).;)_",iter, [&](){return rel_new_eql_10ebb01129546352->size();});
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
}
signalHandler->setMsg(R"_(eql(xy_z,$Add(x, $Add(y, z))) :- 
   add(x,y,xy),
   add(xy,z,xy_z).
in file subsumption.dl [39:1-44:38])_");
{
	Logger logger(R"_(@t-recursive-rule;eql;1;subsumption.dl [39:1-44:38];eql(xy_z,$Add(x, $Add(y, z))) :- \n   add(x,y,xy),\n   add(xy,z,xy_z).;)_",iter, [&](){return rel_new_eql_10ebb01129546352->size();});
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
}
}
{
	Logger logger(R"_(@t-recursive-relation;leader;subsumption.dl [57:7-57:13];)_",iter, [&](){return rel_new_leader_99e6be51e44547e4->size();});
signalHandler->setMsg(R"_(leader(a,as(@generator_0, Id)) :- 
   eql(a,a),
   @generator_0 = min as(b0, number) : { eql(a,b0),as(b0, number) = as(b0, number) }.
in file subsumption.dl [58:1-58:83])_");
{
	Logger logger(R"_(@t-recursive-rule;leader;0;subsumption.dl [58:1-58:83];leader(a,as(@generator_0, Id)) :- \n   eql(a,a),\n   @generator_0 = min as(b0, number) : { eql(a,b0),as(b0, number) = as(b0, number) }.;)_",iter, [&](){return rel_new_leader_99e6be51e44547e4->size();});
if(!(rel_delta_eql_fdc75db4daac3372->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_delta_eql_fdc75db4daac3372_op_ctxt,rel_delta_eql_fdc75db4daac3372->createContext());
CREATE_OP_CONTEXT(rel_new_leader_99e6be51e44547e4_op_ctxt,rel_new_leader_99e6be51e44547e4->createContext());
CREATE_OP_CONTEXT(rel_eql_e1be027843ac9bc5_op_ctxt,rel_eql_e1be027843ac9bc5->createContext());
CREATE_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt,rel_leader_d565398e1ef92697->createContext());
for(const auto& env0 : *rel_delta_eql_fdc75db4daac3372) {
if( (ramBitCast<RamDomain>(env0[0]) == ramBitCast<RamDomain>(env0[1]))) {
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
if( (ramBitCast<RamDomain>(env1[0]) == ramBitCast<RamDomain>(env1[0])) && !(rel_leader_d565398e1ef92697->contains(Tuple<RamDomain,2>{{ramBitCast(env0[0]),ramBitCast(env1[0])}},READ_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt)))) {
Tuple<RamDomain,2> tuple{{ramBitCast(env0[0]),ramBitCast(env1[0])}};
rel_new_leader_99e6be51e44547e4->insert(tuple,READ_OP_CONTEXT(rel_new_leader_99e6be51e44547e4_op_ctxt));
}
}
}
}
}
();}
}
}
{
	Logger logger(R"_(@t-recursive-relation;var;subsumption.dl [9:7-9:10];)_",iter, [&](){return rel_new_var_7aacd8d7c9129d14->size();});
signalHandler->setMsg(R"_(var(x,c1) :- 
   var(x,c),
   leader(c,c1).
in file subsumption.dl [48:1-48:40])_");
{
	Logger logger(R"_(@t-recursive-rule;var;0;subsumption.dl [48:1-48:40];var(x,c1) :- \n   var(x,c),\n   leader(c,c1).;)_",iter, [&](){return rel_new_var_7aacd8d7c9129d14->size();});
if(!(rel_delta_var_789565ec55b51a31->empty()) && !(rel_leader_d565398e1ef92697->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_delta_leader_d4159f531d436f83_op_ctxt,rel_delta_leader_d4159f531d436f83->createContext());
CREATE_OP_CONTEXT(rel_delta_var_789565ec55b51a31_op_ctxt,rel_delta_var_789565ec55b51a31->createContext());
CREATE_OP_CONTEXT(rel_new_var_7aacd8d7c9129d14_op_ctxt,rel_new_var_7aacd8d7c9129d14->createContext());
CREATE_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt,rel_leader_d565398e1ef92697->createContext());
CREATE_OP_CONTEXT(rel_var_09870be8e1a4a08e_op_ctxt,rel_var_09870be8e1a4a08e->createContext());
for(const auto& env0 : *rel_delta_var_789565ec55b51a31) {
auto range = rel_leader_d565398e1ef92697->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt));
for(const auto& env1 : range) {
if( !(rel_var_09870be8e1a4a08e->contains(Tuple<RamDomain,2>{{ramBitCast(env0[0]),ramBitCast(env1[1])}},READ_OP_CONTEXT(rel_var_09870be8e1a4a08e_op_ctxt))) && !(rel_delta_leader_d4159f531d436f83->contains(Tuple<RamDomain,2>{{ramBitCast(env0[1]),ramBitCast(env1[1])}},READ_OP_CONTEXT(rel_delta_leader_d4159f531d436f83_op_ctxt)))) {
Tuple<RamDomain,2> tuple{{ramBitCast(env0[0]),ramBitCast(env1[1])}};
rel_new_var_7aacd8d7c9129d14->insert(tuple,READ_OP_CONTEXT(rel_new_var_7aacd8d7c9129d14_op_ctxt));
}
}
}
}
();}
}
signalHandler->setMsg(R"_(var(x,c1) :- 
   var(x,c),
   leader(c,c1).
in file subsumption.dl [48:1-48:40])_");
{
	Logger logger(R"_(@t-recursive-rule;var;1;subsumption.dl [48:1-48:40];var(x,c1) :- \n   var(x,c),\n   leader(c,c1).;)_",iter, [&](){return rel_new_var_7aacd8d7c9129d14->size();});
if(!(rel_var_09870be8e1a4a08e->empty()) && !(rel_delta_leader_d4159f531d436f83->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_delta_leader_d4159f531d436f83_op_ctxt,rel_delta_leader_d4159f531d436f83->createContext());
CREATE_OP_CONTEXT(rel_new_var_7aacd8d7c9129d14_op_ctxt,rel_new_var_7aacd8d7c9129d14->createContext());
CREATE_OP_CONTEXT(rel_var_09870be8e1a4a08e_op_ctxt,rel_var_09870be8e1a4a08e->createContext());
for(const auto& env0 : *rel_var_09870be8e1a4a08e) {
auto range = rel_delta_leader_d4159f531d436f83->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_delta_leader_d4159f531d436f83_op_ctxt));
for(const auto& env1 : range) {
if( !(rel_var_09870be8e1a4a08e->contains(Tuple<RamDomain,2>{{ramBitCast(env0[0]),ramBitCast(env1[1])}},READ_OP_CONTEXT(rel_var_09870be8e1a4a08e_op_ctxt)))) {
Tuple<RamDomain,2> tuple{{ramBitCast(env0[0]),ramBitCast(env1[1])}};
rel_new_var_7aacd8d7c9129d14->insert(tuple,READ_OP_CONTEXT(rel_new_var_7aacd8d7c9129d14_op_ctxt));
}
}
}
}
();}
}
}
{
	Logger logger(R"_(@t-recursive-relation;add;subsumption.dl [8:7-8:10];)_",iter, [&](){return rel_new_add_954a8c50e586f068->size();});
rel_delta_add_241d705dc2fb23df->purge();
signalHandler->setMsg(R"_(add(x1,y1,c1) <= add(x2,y2,c2) :- 
   leader(x1,x2),
   leader(y1,y2),
   leader(c1,c2). .plan 0:(1,3,4,5,2), 1:(1,3,4,5,2), 2:(1,3,4,5,2), 3:(1,3,4,5,2), 4:(1,3,4,5,2), 5:(1,3,4,5,2)
in file subsumption.dl [50:1-52:123])_");
{
	Logger logger(R"_(@t-recursive-rule;add;0;subsumption.dl [50:1-52:123];add(x1,y1,c1) <= add(x2,y2,c2) :- \n   leader(x1,x2),\n   leader(y1,y2),\n   leader(c1,c2). .plan 0:(1,3,4,5,2), 1:(1,3,4,5,2), 2:(1,3,4,5,2), 3:(1,3,4,5,2), 4:(1,3,4,5,2), 5:(1,3,4,5,2);)_",iter, [&](){return rel_reject_add_d8fb12f9ecd20122->size();});
if(!(rel_new_add_954a8c50e586f068->empty()) && !(rel_leader_d565398e1ef92697->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_new_add_954a8c50e586f068_op_ctxt,rel_new_add_954a8c50e586f068->createContext());
CREATE_OP_CONTEXT(rel_reject_add_d8fb12f9ecd20122_op_ctxt,rel_reject_add_d8fb12f9ecd20122->createContext());
CREATE_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt,rel_leader_d565398e1ef92697->createContext());
for(const auto& env0 : *rel_new_add_954a8c50e586f068) {
auto range = rel_leader_d565398e1ef92697->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt));
for(const auto& env1 : range) {
auto range = rel_leader_d565398e1ef92697->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt));
for(const auto& env2 : range) {
auto range = rel_leader_d565398e1ef92697->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[2]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[2]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt));
for(const auto& env3 : range) {
if( !((ramBitCast<RamDomain>(env0[2]) == ramBitCast<RamDomain>(env3[1])) && (ramBitCast<RamDomain>(env0[0]) == ramBitCast<RamDomain>(env1[1])) && (ramBitCast<RamDomain>(env0[1]) == ramBitCast<RamDomain>(env2[1]))) && rel_new_add_954a8c50e586f068->contains(Tuple<RamDomain,3>{{ramBitCast(env1[1]),ramBitCast(env2[1]),ramBitCast(env3[1])}},READ_OP_CONTEXT(rel_new_add_954a8c50e586f068_op_ctxt))) {
Tuple<RamDomain,3> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1]),ramBitCast(env0[2])}};
rel_reject_add_d8fb12f9ecd20122->insert(tuple,READ_OP_CONTEXT(rel_reject_add_d8fb12f9ecd20122_op_ctxt));
}
}
}
}
}
}
();}
}
signalHandler->setMsg(R"_(add(x1,y1,c1) <= add(x2,y2,c2) :- 
   leader(x1,x2),
   leader(y1,y2),
   leader(c1,c2). .plan 0:(1,3,4,5,2), 1:(1,3,4,5,2), 2:(1,3,4,5,2), 3:(1,3,4,5,2), 4:(1,3,4,5,2), 5:(1,3,4,5,2)
in file subsumption.dl [50:1-52:123])_");
{
	Logger logger(R"_(@t-recursive-rule;add;0;subsumption.dl [50:1-52:123];add(x1,y1,c1) <= add(x2,y2,c2) :- \n   leader(x1,x2),\n   leader(y1,y2),\n   leader(c1,c2). .plan 0:(1,3,4,5,2), 1:(1,3,4,5,2), 2:(1,3,4,5,2), 3:(1,3,4,5,2), 4:(1,3,4,5,2), 5:(1,3,4,5,2);)_",iter, [&](){return rel_reject_add_d8fb12f9ecd20122->size();});
if(!(rel_leader_d565398e1ef92697->empty()) && !(rel_new_add_954a8c50e586f068->empty()) && !(rel_add_48c57da858454f79->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_new_add_954a8c50e586f068_op_ctxt,rel_new_add_954a8c50e586f068->createContext());
CREATE_OP_CONTEXT(rel_reject_add_d8fb12f9ecd20122_op_ctxt,rel_reject_add_d8fb12f9ecd20122->createContext());
CREATE_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt,rel_add_48c57da858454f79->createContext());
CREATE_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt,rel_leader_d565398e1ef92697->createContext());
for(const auto& env0 : *rel_new_add_954a8c50e586f068) {
auto range = rel_leader_d565398e1ef92697->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt));
for(const auto& env1 : range) {
auto range = rel_leader_d565398e1ef92697->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt));
for(const auto& env2 : range) {
auto range = rel_leader_d565398e1ef92697->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[2]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[2]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt));
for(const auto& env3 : range) {
if( rel_add_48c57da858454f79->contains(Tuple<RamDomain,3>{{ramBitCast(env1[1]),ramBitCast(env2[1]),ramBitCast(env3[1])}},READ_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt))) {
Tuple<RamDomain,3> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1]),ramBitCast(env0[2])}};
rel_reject_add_d8fb12f9ecd20122->insert(tuple,READ_OP_CONTEXT(rel_reject_add_d8fb12f9ecd20122_op_ctxt));
break;
}
}
}
}
}
}
();}
}
signalHandler->setMsg(R"_(add(x1,y1,c1) <= add(x2,y2,c2) :- 
   leader(x1,x2),
   leader(y1,y2),
   leader(c1,c2). .plan 0:(1,3,4,5,2), 1:(1,3,4,5,2), 2:(1,3,4,5,2), 3:(1,3,4,5,2), 4:(1,3,4,5,2), 5:(1,3,4,5,2)
in file subsumption.dl [50:1-52:123])_");
{
	Logger logger(R"_(@t-recursive-rule;add;1;subsumption.dl [50:1-52:123];add(x1,y1,c1) <= add(x2,y2,c2) :- \n   leader(x1,x2),\n   leader(y1,y2),\n   leader(c1,c2). .plan 0:(1,3,4,5,2), 1:(1,3,4,5,2), 2:(1,3,4,5,2), 3:(1,3,4,5,2), 4:(1,3,4,5,2), 5:(1,3,4,5,2);)_",iter, [&](){return rel_reject_add_d8fb12f9ecd20122->size();});
if(!(rel_leader_d565398e1ef92697->empty()) && !(rel_delta_leader_d4159f531d436f83->empty()) && !(rel_new_add_954a8c50e586f068->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_delta_leader_d4159f531d436f83_op_ctxt,rel_delta_leader_d4159f531d436f83->createContext());
CREATE_OP_CONTEXT(rel_new_add_954a8c50e586f068_op_ctxt,rel_new_add_954a8c50e586f068->createContext());
CREATE_OP_CONTEXT(rel_reject_add_d8fb12f9ecd20122_op_ctxt,rel_reject_add_d8fb12f9ecd20122->createContext());
CREATE_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt,rel_leader_d565398e1ef92697->createContext());
for(const auto& env0 : *rel_new_add_954a8c50e586f068) {
auto range = rel_delta_leader_d4159f531d436f83->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_delta_leader_d4159f531d436f83_op_ctxt));
for(const auto& env1 : range) {
auto range = rel_leader_d565398e1ef92697->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt));
for(const auto& env2 : range) {
auto range = rel_leader_d565398e1ef92697->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[2]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[2]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt));
for(const auto& env3 : range) {
if( !((ramBitCast<RamDomain>(env0[2]) == ramBitCast<RamDomain>(env3[1])) && (ramBitCast<RamDomain>(env0[0]) == ramBitCast<RamDomain>(env1[1])) && (ramBitCast<RamDomain>(env0[1]) == ramBitCast<RamDomain>(env2[1]))) && rel_new_add_954a8c50e586f068->contains(Tuple<RamDomain,3>{{ramBitCast(env1[1]),ramBitCast(env2[1]),ramBitCast(env3[1])}},READ_OP_CONTEXT(rel_new_add_954a8c50e586f068_op_ctxt))) {
Tuple<RamDomain,3> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1]),ramBitCast(env0[2])}};
rel_reject_add_d8fb12f9ecd20122->insert(tuple,READ_OP_CONTEXT(rel_reject_add_d8fb12f9ecd20122_op_ctxt));
}
}
}
}
}
}
();}
}
signalHandler->setMsg(R"_(add(x1,y1,c1) <= add(x2,y2,c2) :- 
   leader(x1,x2),
   leader(y1,y2),
   leader(c1,c2). .plan 0:(1,3,4,5,2), 1:(1,3,4,5,2), 2:(1,3,4,5,2), 3:(1,3,4,5,2), 4:(1,3,4,5,2), 5:(1,3,4,5,2)
in file subsumption.dl [50:1-52:123])_");
{
	Logger logger(R"_(@t-recursive-rule;add;1;subsumption.dl [50:1-52:123];add(x1,y1,c1) <= add(x2,y2,c2) :- \n   leader(x1,x2),\n   leader(y1,y2),\n   leader(c1,c2). .plan 0:(1,3,4,5,2), 1:(1,3,4,5,2), 2:(1,3,4,5,2), 3:(1,3,4,5,2), 4:(1,3,4,5,2), 5:(1,3,4,5,2);)_",iter, [&](){return rel_reject_add_d8fb12f9ecd20122->size();});
if(!(rel_leader_d565398e1ef92697->empty()) && !(rel_new_add_954a8c50e586f068->empty()) && !(rel_add_48c57da858454f79->empty()) && !(rel_delta_leader_d4159f531d436f83->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_delta_leader_d4159f531d436f83_op_ctxt,rel_delta_leader_d4159f531d436f83->createContext());
CREATE_OP_CONTEXT(rel_new_add_954a8c50e586f068_op_ctxt,rel_new_add_954a8c50e586f068->createContext());
CREATE_OP_CONTEXT(rel_reject_add_d8fb12f9ecd20122_op_ctxt,rel_reject_add_d8fb12f9ecd20122->createContext());
CREATE_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt,rel_add_48c57da858454f79->createContext());
CREATE_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt,rel_leader_d565398e1ef92697->createContext());
for(const auto& env0 : *rel_new_add_954a8c50e586f068) {
auto range = rel_delta_leader_d4159f531d436f83->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_delta_leader_d4159f531d436f83_op_ctxt));
for(const auto& env1 : range) {
auto range = rel_leader_d565398e1ef92697->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt));
for(const auto& env2 : range) {
auto range = rel_leader_d565398e1ef92697->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[2]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[2]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt));
for(const auto& env3 : range) {
if( rel_add_48c57da858454f79->contains(Tuple<RamDomain,3>{{ramBitCast(env1[1]),ramBitCast(env2[1]),ramBitCast(env3[1])}},READ_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt))) {
Tuple<RamDomain,3> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1]),ramBitCast(env0[2])}};
rel_reject_add_d8fb12f9ecd20122->insert(tuple,READ_OP_CONTEXT(rel_reject_add_d8fb12f9ecd20122_op_ctxt));
break;
}
}
}
}
}
}
();}
}
signalHandler->setMsg(R"_(add(x1,y1,c1) <= add(x2,y2,c2) :- 
   leader(x1,x2),
   leader(y1,y2),
   leader(c1,c2). .plan 0:(1,3,4,5,2), 1:(1,3,4,5,2), 2:(1,3,4,5,2), 3:(1,3,4,5,2), 4:(1,3,4,5,2), 5:(1,3,4,5,2)
in file subsumption.dl [50:1-52:123])_");
{
	Logger logger(R"_(@t-recursive-rule;add;2;subsumption.dl [50:1-52:123];add(x1,y1,c1) <= add(x2,y2,c2) :- \n   leader(x1,x2),\n   leader(y1,y2),\n   leader(c1,c2). .plan 0:(1,3,4,5,2), 1:(1,3,4,5,2), 2:(1,3,4,5,2), 3:(1,3,4,5,2), 4:(1,3,4,5,2), 5:(1,3,4,5,2);)_",iter, [&](){return rel_reject_add_d8fb12f9ecd20122->size();});
if(!(rel_leader_d565398e1ef92697->empty()) && !(rel_delta_leader_d4159f531d436f83->empty()) && !(rel_new_add_954a8c50e586f068->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_delta_leader_d4159f531d436f83_op_ctxt,rel_delta_leader_d4159f531d436f83->createContext());
CREATE_OP_CONTEXT(rel_new_add_954a8c50e586f068_op_ctxt,rel_new_add_954a8c50e586f068->createContext());
CREATE_OP_CONTEXT(rel_reject_add_d8fb12f9ecd20122_op_ctxt,rel_reject_add_d8fb12f9ecd20122->createContext());
CREATE_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt,rel_leader_d565398e1ef92697->createContext());
for(const auto& env0 : *rel_new_add_954a8c50e586f068) {
auto range = rel_delta_leader_d4159f531d436f83->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_delta_leader_d4159f531d436f83_op_ctxt));
for(const auto& env1 : range) {
auto range = rel_delta_leader_d4159f531d436f83->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_delta_leader_d4159f531d436f83_op_ctxt));
for(const auto& env2 : range) {
auto range = rel_leader_d565398e1ef92697->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[2]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[2]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt));
for(const auto& env3 : range) {
if( !((ramBitCast<RamDomain>(env0[2]) == ramBitCast<RamDomain>(env3[1])) && (ramBitCast<RamDomain>(env0[0]) == ramBitCast<RamDomain>(env1[1])) && (ramBitCast<RamDomain>(env0[1]) == ramBitCast<RamDomain>(env2[1]))) && rel_new_add_954a8c50e586f068->contains(Tuple<RamDomain,3>{{ramBitCast(env1[1]),ramBitCast(env2[1]),ramBitCast(env3[1])}},READ_OP_CONTEXT(rel_new_add_954a8c50e586f068_op_ctxt))) {
Tuple<RamDomain,3> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1]),ramBitCast(env0[2])}};
rel_reject_add_d8fb12f9ecd20122->insert(tuple,READ_OP_CONTEXT(rel_reject_add_d8fb12f9ecd20122_op_ctxt));
}
}
}
}
}
}
();}
}
signalHandler->setMsg(R"_(add(x1,y1,c1) <= add(x2,y2,c2) :- 
   leader(x1,x2),
   leader(y1,y2),
   leader(c1,c2). .plan 0:(1,3,4,5,2), 1:(1,3,4,5,2), 2:(1,3,4,5,2), 3:(1,3,4,5,2), 4:(1,3,4,5,2), 5:(1,3,4,5,2)
in file subsumption.dl [50:1-52:123])_");
{
	Logger logger(R"_(@t-recursive-rule;add;2;subsumption.dl [50:1-52:123];add(x1,y1,c1) <= add(x2,y2,c2) :- \n   leader(x1,x2),\n   leader(y1,y2),\n   leader(c1,c2). .plan 0:(1,3,4,5,2), 1:(1,3,4,5,2), 2:(1,3,4,5,2), 3:(1,3,4,5,2), 4:(1,3,4,5,2), 5:(1,3,4,5,2);)_",iter, [&](){return rel_reject_add_d8fb12f9ecd20122->size();});
if(!(rel_leader_d565398e1ef92697->empty()) && !(rel_delta_leader_d4159f531d436f83->empty()) && !(rel_add_48c57da858454f79->empty()) && !(rel_new_add_954a8c50e586f068->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_delta_leader_d4159f531d436f83_op_ctxt,rel_delta_leader_d4159f531d436f83->createContext());
CREATE_OP_CONTEXT(rel_new_add_954a8c50e586f068_op_ctxt,rel_new_add_954a8c50e586f068->createContext());
CREATE_OP_CONTEXT(rel_reject_add_d8fb12f9ecd20122_op_ctxt,rel_reject_add_d8fb12f9ecd20122->createContext());
CREATE_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt,rel_add_48c57da858454f79->createContext());
CREATE_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt,rel_leader_d565398e1ef92697->createContext());
for(const auto& env0 : *rel_new_add_954a8c50e586f068) {
auto range = rel_delta_leader_d4159f531d436f83->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_delta_leader_d4159f531d436f83_op_ctxt));
for(const auto& env1 : range) {
auto range = rel_delta_leader_d4159f531d436f83->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_delta_leader_d4159f531d436f83_op_ctxt));
for(const auto& env2 : range) {
auto range = rel_leader_d565398e1ef92697->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[2]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[2]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt));
for(const auto& env3 : range) {
if( rel_add_48c57da858454f79->contains(Tuple<RamDomain,3>{{ramBitCast(env1[1]),ramBitCast(env2[1]),ramBitCast(env3[1])}},READ_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt))) {
Tuple<RamDomain,3> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1]),ramBitCast(env0[2])}};
rel_reject_add_d8fb12f9ecd20122->insert(tuple,READ_OP_CONTEXT(rel_reject_add_d8fb12f9ecd20122_op_ctxt));
break;
}
}
}
}
}
}
();}
}
signalHandler->setMsg(R"_(add(x1,y1,c1) <= add(x2,y2,c2) :- 
   leader(x1,x2),
   leader(y1,y2),
   leader(c1,c2). .plan 0:(1,3,4,5,2), 1:(1,3,4,5,2), 2:(1,3,4,5,2), 3:(1,3,4,5,2), 4:(1,3,4,5,2), 5:(1,3,4,5,2)
in file subsumption.dl [50:1-52:123])_");
{
	Logger logger(R"_(@t-recursive-rule;add;3;subsumption.dl [50:1-52:123];add(x1,y1,c1) <= add(x2,y2,c2) :- \n   leader(x1,x2),\n   leader(y1,y2),\n   leader(c1,c2). .plan 0:(1,3,4,5,2), 1:(1,3,4,5,2), 2:(1,3,4,5,2), 3:(1,3,4,5,2), 4:(1,3,4,5,2), 5:(1,3,4,5,2);)_",iter, [&](){return rel_reject_add_d8fb12f9ecd20122->size();});
if(!(rel_delta_leader_d4159f531d436f83->empty()) && !(rel_leader_d565398e1ef92697->empty()) && !(rel_new_add_954a8c50e586f068->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_delta_leader_d4159f531d436f83_op_ctxt,rel_delta_leader_d4159f531d436f83->createContext());
CREATE_OP_CONTEXT(rel_new_add_954a8c50e586f068_op_ctxt,rel_new_add_954a8c50e586f068->createContext());
CREATE_OP_CONTEXT(rel_reject_add_d8fb12f9ecd20122_op_ctxt,rel_reject_add_d8fb12f9ecd20122->createContext());
CREATE_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt,rel_leader_d565398e1ef92697->createContext());
for(const auto& env0 : *rel_new_add_954a8c50e586f068) {
auto range = rel_leader_d565398e1ef92697->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt));
for(const auto& env1 : range) {
auto range = rel_delta_leader_d4159f531d436f83->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_delta_leader_d4159f531d436f83_op_ctxt));
for(const auto& env2 : range) {
auto range = rel_delta_leader_d4159f531d436f83->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[2]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[2]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_delta_leader_d4159f531d436f83_op_ctxt));
for(const auto& env3 : range) {
if( !((ramBitCast<RamDomain>(env0[2]) == ramBitCast<RamDomain>(env3[1])) && (ramBitCast<RamDomain>(env0[0]) == ramBitCast<RamDomain>(env1[1])) && (ramBitCast<RamDomain>(env0[1]) == ramBitCast<RamDomain>(env2[1]))) && rel_new_add_954a8c50e586f068->contains(Tuple<RamDomain,3>{{ramBitCast(env1[1]),ramBitCast(env2[1]),ramBitCast(env3[1])}},READ_OP_CONTEXT(rel_new_add_954a8c50e586f068_op_ctxt))) {
Tuple<RamDomain,3> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1]),ramBitCast(env0[2])}};
rel_reject_add_d8fb12f9ecd20122->insert(tuple,READ_OP_CONTEXT(rel_reject_add_d8fb12f9ecd20122_op_ctxt));
}
}
}
}
}
}
();}
}
signalHandler->setMsg(R"_(add(x1,y1,c1) <= add(x2,y2,c2) :- 
   leader(x1,x2),
   leader(y1,y2),
   leader(c1,c2). .plan 0:(1,3,4,5,2), 1:(1,3,4,5,2), 2:(1,3,4,5,2), 3:(1,3,4,5,2), 4:(1,3,4,5,2), 5:(1,3,4,5,2)
in file subsumption.dl [50:1-52:123])_");
{
	Logger logger(R"_(@t-recursive-rule;add;3;subsumption.dl [50:1-52:123];add(x1,y1,c1) <= add(x2,y2,c2) :- \n   leader(x1,x2),\n   leader(y1,y2),\n   leader(c1,c2). .plan 0:(1,3,4,5,2), 1:(1,3,4,5,2), 2:(1,3,4,5,2), 3:(1,3,4,5,2), 4:(1,3,4,5,2), 5:(1,3,4,5,2);)_",iter, [&](){return rel_reject_add_d8fb12f9ecd20122->size();});
if(!(rel_delta_leader_d4159f531d436f83->empty()) && !(rel_new_add_954a8c50e586f068->empty()) && !(rel_add_48c57da858454f79->empty()) && !(rel_leader_d565398e1ef92697->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_delta_leader_d4159f531d436f83_op_ctxt,rel_delta_leader_d4159f531d436f83->createContext());
CREATE_OP_CONTEXT(rel_new_add_954a8c50e586f068_op_ctxt,rel_new_add_954a8c50e586f068->createContext());
CREATE_OP_CONTEXT(rel_reject_add_d8fb12f9ecd20122_op_ctxt,rel_reject_add_d8fb12f9ecd20122->createContext());
CREATE_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt,rel_add_48c57da858454f79->createContext());
CREATE_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt,rel_leader_d565398e1ef92697->createContext());
for(const auto& env0 : *rel_new_add_954a8c50e586f068) {
auto range = rel_leader_d565398e1ef92697->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt));
for(const auto& env1 : range) {
auto range = rel_delta_leader_d4159f531d436f83->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_delta_leader_d4159f531d436f83_op_ctxt));
for(const auto& env2 : range) {
auto range = rel_delta_leader_d4159f531d436f83->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[2]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[2]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_delta_leader_d4159f531d436f83_op_ctxt));
for(const auto& env3 : range) {
if( rel_add_48c57da858454f79->contains(Tuple<RamDomain,3>{{ramBitCast(env1[1]),ramBitCast(env2[1]),ramBitCast(env3[1])}},READ_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt))) {
Tuple<RamDomain,3> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1]),ramBitCast(env0[2])}};
rel_reject_add_d8fb12f9ecd20122->insert(tuple,READ_OP_CONTEXT(rel_reject_add_d8fb12f9ecd20122_op_ctxt));
break;
}
}
}
}
}
}
();}
}
[&](){
CREATE_OP_CONTEXT(rel_delta_add_241d705dc2fb23df_op_ctxt,rel_delta_add_241d705dc2fb23df->createContext());
CREATE_OP_CONTEXT(rel_new_add_954a8c50e586f068_op_ctxt,rel_new_add_954a8c50e586f068->createContext());
CREATE_OP_CONTEXT(rel_reject_add_d8fb12f9ecd20122_op_ctxt,rel_reject_add_d8fb12f9ecd20122->createContext());
for(const auto& env0 : *rel_new_add_954a8c50e586f068) {
if( !(rel_reject_add_d8fb12f9ecd20122->contains(Tuple<RamDomain,3>{{ramBitCast(env0[0]),ramBitCast(env0[1]),ramBitCast(env0[2])}},READ_OP_CONTEXT(rel_reject_add_d8fb12f9ecd20122_op_ctxt)))) {
Tuple<RamDomain,3> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1]),ramBitCast(env0[2])}};
rel_delta_add_241d705dc2fb23df->insert(tuple,READ_OP_CONTEXT(rel_delta_add_241d705dc2fb23df_op_ctxt));
}
}
}
();rel_reject_add_d8fb12f9ecd20122->purge();
rel_new_add_954a8c50e586f068->purge();
signalHandler->setMsg(R"_(add(x1,y1,c1) <= add(x2,y2,c2) :- 
   leader(x1,x2),
   leader(y1,y2),
   leader(c1,c2). .plan 0:(1,3,4,5,2), 1:(1,3,4,5,2), 2:(1,3,4,5,2), 3:(1,3,4,5,2), 4:(1,3,4,5,2), 5:(1,3,4,5,2)
in file subsumption.dl [50:1-52:123])_");
{
	Logger logger(R"_(@t-recursive-rule;add;0;subsumption.dl [50:1-52:123];add(x1,y1,c1) <= add(x2,y2,c2) :- \n   leader(x1,x2),\n   leader(y1,y2),\n   leader(c1,c2). .plan 0:(1,3,4,5,2), 1:(1,3,4,5,2), 2:(1,3,4,5,2), 3:(1,3,4,5,2), 4:(1,3,4,5,2), 5:(1,3,4,5,2);)_",iter, [&](){return rel_delete_add_6fd868847292dbea->size();});
if(!(rel_add_48c57da858454f79->empty()) && !(rel_leader_d565398e1ef92697->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_delete_add_6fd868847292dbea_op_ctxt,rel_delete_add_6fd868847292dbea->createContext());
CREATE_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt,rel_add_48c57da858454f79->createContext());
CREATE_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt,rel_leader_d565398e1ef92697->createContext());
for(const auto& env0 : *rel_add_48c57da858454f79) {
auto range = rel_leader_d565398e1ef92697->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt));
for(const auto& env1 : range) {
auto range = rel_leader_d565398e1ef92697->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt));
for(const auto& env2 : range) {
auto range = rel_leader_d565398e1ef92697->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[2]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[2]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt));
for(const auto& env3 : range) {
if( !((ramBitCast<RamDomain>(env0[2]) == ramBitCast<RamDomain>(env3[1])) && (ramBitCast<RamDomain>(env0[0]) == ramBitCast<RamDomain>(env1[1])) && (ramBitCast<RamDomain>(env0[1]) == ramBitCast<RamDomain>(env2[1]))) && rel_add_48c57da858454f79->contains(Tuple<RamDomain,3>{{ramBitCast(env1[1]),ramBitCast(env2[1]),ramBitCast(env3[1])}},READ_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt))) {
Tuple<RamDomain,3> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1]),ramBitCast(env0[2])}};
rel_delete_add_6fd868847292dbea->insert(tuple,READ_OP_CONTEXT(rel_delete_add_6fd868847292dbea_op_ctxt));
}
}
}
}
}
}
();}
}
signalHandler->setMsg(R"_(add(x1,y1,c1) <= add(x2,y2,c2) :- 
   leader(x1,x2),
   leader(y1,y2),
   leader(c1,c2). .plan 0:(1,3,4,5,2), 1:(1,3,4,5,2), 2:(1,3,4,5,2), 3:(1,3,4,5,2), 4:(1,3,4,5,2), 5:(1,3,4,5,2)
in file subsumption.dl [50:1-52:123])_");
{
	Logger logger(R"_(@t-recursive-rule;add;1;subsumption.dl [50:1-52:123];add(x1,y1,c1) <= add(x2,y2,c2) :- \n   leader(x1,x2),\n   leader(y1,y2),\n   leader(c1,c2). .plan 0:(1,3,4,5,2), 1:(1,3,4,5,2), 2:(1,3,4,5,2), 3:(1,3,4,5,2), 4:(1,3,4,5,2), 5:(1,3,4,5,2);)_",iter, [&](){return rel_delete_add_6fd868847292dbea->size();});
if(!(rel_leader_d565398e1ef92697->empty()) && !(rel_delta_leader_d4159f531d436f83->empty()) && !(rel_add_48c57da858454f79->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_delete_add_6fd868847292dbea_op_ctxt,rel_delete_add_6fd868847292dbea->createContext());
CREATE_OP_CONTEXT(rel_delta_leader_d4159f531d436f83_op_ctxt,rel_delta_leader_d4159f531d436f83->createContext());
CREATE_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt,rel_add_48c57da858454f79->createContext());
CREATE_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt,rel_leader_d565398e1ef92697->createContext());
for(const auto& env0 : *rel_add_48c57da858454f79) {
auto range = rel_delta_leader_d4159f531d436f83->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_delta_leader_d4159f531d436f83_op_ctxt));
for(const auto& env1 : range) {
auto range = rel_leader_d565398e1ef92697->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt));
for(const auto& env2 : range) {
auto range = rel_leader_d565398e1ef92697->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[2]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[2]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt));
for(const auto& env3 : range) {
if( !((ramBitCast<RamDomain>(env0[2]) == ramBitCast<RamDomain>(env3[1])) && (ramBitCast<RamDomain>(env0[0]) == ramBitCast<RamDomain>(env1[1])) && (ramBitCast<RamDomain>(env0[1]) == ramBitCast<RamDomain>(env2[1]))) && rel_add_48c57da858454f79->contains(Tuple<RamDomain,3>{{ramBitCast(env1[1]),ramBitCast(env2[1]),ramBitCast(env3[1])}},READ_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt))) {
Tuple<RamDomain,3> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1]),ramBitCast(env0[2])}};
rel_delete_add_6fd868847292dbea->insert(tuple,READ_OP_CONTEXT(rel_delete_add_6fd868847292dbea_op_ctxt));
}
}
}
}
}
}
();}
}
signalHandler->setMsg(R"_(add(x1,y1,c1) <= add(x2,y2,c2) :- 
   leader(x1,x2),
   leader(y1,y2),
   leader(c1,c2). .plan 0:(1,3,4,5,2), 1:(1,3,4,5,2), 2:(1,3,4,5,2), 3:(1,3,4,5,2), 4:(1,3,4,5,2), 5:(1,3,4,5,2)
in file subsumption.dl [50:1-52:123])_");
{
	Logger logger(R"_(@t-recursive-rule;add;2;subsumption.dl [50:1-52:123];add(x1,y1,c1) <= add(x2,y2,c2) :- \n   leader(x1,x2),\n   leader(y1,y2),\n   leader(c1,c2). .plan 0:(1,3,4,5,2), 1:(1,3,4,5,2), 2:(1,3,4,5,2), 3:(1,3,4,5,2), 4:(1,3,4,5,2), 5:(1,3,4,5,2);)_",iter, [&](){return rel_delete_add_6fd868847292dbea->size();});
if(!(rel_leader_d565398e1ef92697->empty()) && !(rel_delta_leader_d4159f531d436f83->empty()) && !(rel_add_48c57da858454f79->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_delete_add_6fd868847292dbea_op_ctxt,rel_delete_add_6fd868847292dbea->createContext());
CREATE_OP_CONTEXT(rel_delta_leader_d4159f531d436f83_op_ctxt,rel_delta_leader_d4159f531d436f83->createContext());
CREATE_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt,rel_add_48c57da858454f79->createContext());
CREATE_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt,rel_leader_d565398e1ef92697->createContext());
for(const auto& env0 : *rel_add_48c57da858454f79) {
auto range = rel_delta_leader_d4159f531d436f83->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_delta_leader_d4159f531d436f83_op_ctxt));
for(const auto& env1 : range) {
auto range = rel_delta_leader_d4159f531d436f83->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_delta_leader_d4159f531d436f83_op_ctxt));
for(const auto& env2 : range) {
auto range = rel_leader_d565398e1ef92697->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[2]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[2]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt));
for(const auto& env3 : range) {
if( !((ramBitCast<RamDomain>(env0[2]) == ramBitCast<RamDomain>(env3[1])) && (ramBitCast<RamDomain>(env0[0]) == ramBitCast<RamDomain>(env1[1])) && (ramBitCast<RamDomain>(env0[1]) == ramBitCast<RamDomain>(env2[1]))) && rel_add_48c57da858454f79->contains(Tuple<RamDomain,3>{{ramBitCast(env1[1]),ramBitCast(env2[1]),ramBitCast(env3[1])}},READ_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt))) {
Tuple<RamDomain,3> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1]),ramBitCast(env0[2])}};
rel_delete_add_6fd868847292dbea->insert(tuple,READ_OP_CONTEXT(rel_delete_add_6fd868847292dbea_op_ctxt));
}
}
}
}
}
}
();}
}
signalHandler->setMsg(R"_(add(x1,y1,c1) <= add(x2,y2,c2) :- 
   leader(x1,x2),
   leader(y1,y2),
   leader(c1,c2). .plan 0:(1,3,4,5,2), 1:(1,3,4,5,2), 2:(1,3,4,5,2), 3:(1,3,4,5,2), 4:(1,3,4,5,2), 5:(1,3,4,5,2)
in file subsumption.dl [50:1-52:123])_");
{
	Logger logger(R"_(@t-recursive-rule;add;3;subsumption.dl [50:1-52:123];add(x1,y1,c1) <= add(x2,y2,c2) :- \n   leader(x1,x2),\n   leader(y1,y2),\n   leader(c1,c2). .plan 0:(1,3,4,5,2), 1:(1,3,4,5,2), 2:(1,3,4,5,2), 3:(1,3,4,5,2), 4:(1,3,4,5,2), 5:(1,3,4,5,2);)_",iter, [&](){return rel_delete_add_6fd868847292dbea->size();});
if(!(rel_delta_leader_d4159f531d436f83->empty()) && !(rel_leader_d565398e1ef92697->empty()) && !(rel_add_48c57da858454f79->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_delete_add_6fd868847292dbea_op_ctxt,rel_delete_add_6fd868847292dbea->createContext());
CREATE_OP_CONTEXT(rel_delta_leader_d4159f531d436f83_op_ctxt,rel_delta_leader_d4159f531d436f83->createContext());
CREATE_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt,rel_add_48c57da858454f79->createContext());
CREATE_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt,rel_leader_d565398e1ef92697->createContext());
for(const auto& env0 : *rel_add_48c57da858454f79) {
auto range = rel_leader_d565398e1ef92697->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt));
for(const auto& env1 : range) {
auto range = rel_delta_leader_d4159f531d436f83->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_delta_leader_d4159f531d436f83_op_ctxt));
for(const auto& env2 : range) {
auto range = rel_delta_leader_d4159f531d436f83->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[2]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[2]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_delta_leader_d4159f531d436f83_op_ctxt));
for(const auto& env3 : range) {
if( !((ramBitCast<RamDomain>(env0[2]) == ramBitCast<RamDomain>(env3[1])) && (ramBitCast<RamDomain>(env0[0]) == ramBitCast<RamDomain>(env1[1])) && (ramBitCast<RamDomain>(env0[1]) == ramBitCast<RamDomain>(env2[1]))) && rel_add_48c57da858454f79->contains(Tuple<RamDomain,3>{{ramBitCast(env1[1]),ramBitCast(env2[1]),ramBitCast(env3[1])}},READ_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt))) {
Tuple<RamDomain,3> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1]),ramBitCast(env0[2])}};
rel_delete_add_6fd868847292dbea->insert(tuple,READ_OP_CONTEXT(rel_delete_add_6fd868847292dbea_op_ctxt));
}
}
}
}
}
}
();}
}
[&](){
CREATE_OP_CONTEXT(rel_delete_add_6fd868847292dbea_op_ctxt,rel_delete_add_6fd868847292dbea->createContext());
for(const auto& env0 : *rel_delete_add_6fd868847292dbea) {
Tuple<RamDomain,3> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1]),ramBitCast(env0[2])}};
rel_add_48c57da858454f79->erase(tuple);
}
}
();rel_delete_add_6fd868847292dbea->purge();
}
{
	Logger logger(R"_(@t-recursive-relation;eql;subsumption.dl [7:7-7:10];)_",iter, [&](){return rel_new_eql_10ebb01129546352->size();});
}
{
	Logger logger(R"_(@t-recursive-relation;leader;subsumption.dl [57:7-57:13];)_",iter, [&](){return rel_new_leader_99e6be51e44547e4->size();});
rel_delta_leader_d4159f531d436f83->purge();
signalHandler->setMsg(R"_(leader(x,y1) <= leader(x,y2) :- 
   as(y1, number) <= as(y2, number).
in file subsumption.dl [59:1-60:38])_");
{
	Logger logger(R"_(@t-recursive-rule;leader;0;subsumption.dl [59:1-60:38];leader(x,y1) <= leader(x,y2) :- \n   as(y1, number) <= as(y2, number).;)_",iter, [&](){return rel_reject_leader_c121991f9eab43a8->size();});
if(!(rel_new_leader_99e6be51e44547e4->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_new_leader_99e6be51e44547e4_op_ctxt,rel_new_leader_99e6be51e44547e4->createContext());
CREATE_OP_CONTEXT(rel_reject_leader_c121991f9eab43a8_op_ctxt,rel_reject_leader_c121991f9eab43a8->createContext());
for(const auto& env0 : *rel_new_leader_99e6be51e44547e4) {
auto range = rel_new_leader_99e6be51e44547e4->lowerUpperRange_12(Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast(env0[1])}},Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_new_leader_99e6be51e44547e4_op_ctxt));
for(const auto& env1 : range) {
if( !((ramBitCast<RamDomain>(env0[1]) == ramBitCast<RamDomain>(env1[1])))) {
Tuple<RamDomain,2> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1])}};
rel_reject_leader_c121991f9eab43a8->insert(tuple,READ_OP_CONTEXT(rel_reject_leader_c121991f9eab43a8_op_ctxt));
break;
}
}
}
}
();}
}
signalHandler->setMsg(R"_(leader(x,y1) <= leader(x,y2) :- 
   as(y1, number) <= as(y2, number).
in file subsumption.dl [59:1-60:38])_");
{
	Logger logger(R"_(@t-recursive-rule;leader;0;subsumption.dl [59:1-60:38];leader(x,y1) <= leader(x,y2) :- \n   as(y1, number) <= as(y2, number).;)_",iter, [&](){return rel_reject_leader_c121991f9eab43a8->size();});
if(!(rel_new_leader_99e6be51e44547e4->empty()) && !(rel_leader_d565398e1ef92697->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_new_leader_99e6be51e44547e4_op_ctxt,rel_new_leader_99e6be51e44547e4->createContext());
CREATE_OP_CONTEXT(rel_reject_leader_c121991f9eab43a8_op_ctxt,rel_reject_leader_c121991f9eab43a8->createContext());
CREATE_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt,rel_leader_d565398e1ef92697->createContext());
for(const auto& env0 : *rel_new_leader_99e6be51e44547e4) {
auto range = rel_leader_d565398e1ef92697->lowerUpperRange_12(Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast(env0[1])}},Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt));
for(const auto& env1 : range) {
if( true) {
Tuple<RamDomain,2> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1])}};
rel_reject_leader_c121991f9eab43a8->insert(tuple,READ_OP_CONTEXT(rel_reject_leader_c121991f9eab43a8_op_ctxt));
break;
}
}
}
}
();}
}
[&](){
CREATE_OP_CONTEXT(rel_delta_leader_d4159f531d436f83_op_ctxt,rel_delta_leader_d4159f531d436f83->createContext());
CREATE_OP_CONTEXT(rel_new_leader_99e6be51e44547e4_op_ctxt,rel_new_leader_99e6be51e44547e4->createContext());
CREATE_OP_CONTEXT(rel_reject_leader_c121991f9eab43a8_op_ctxt,rel_reject_leader_c121991f9eab43a8->createContext());
for(const auto& env0 : *rel_new_leader_99e6be51e44547e4) {
if( !(rel_reject_leader_c121991f9eab43a8->contains(Tuple<RamDomain,2>{{ramBitCast(env0[0]),ramBitCast(env0[1])}},READ_OP_CONTEXT(rel_reject_leader_c121991f9eab43a8_op_ctxt)))) {
Tuple<RamDomain,2> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1])}};
rel_delta_leader_d4159f531d436f83->insert(tuple,READ_OP_CONTEXT(rel_delta_leader_d4159f531d436f83_op_ctxt));
}
}
}
();rel_reject_leader_c121991f9eab43a8->purge();
rel_new_leader_99e6be51e44547e4->purge();
signalHandler->setMsg(R"_(leader(x,y1) <= leader(x,y2) :- 
   as(y1, number) <= as(y2, number).
in file subsumption.dl [59:1-60:38])_");
{
	Logger logger(R"_(@t-recursive-rule;leader;0;subsumption.dl [59:1-60:38];leader(x,y1) <= leader(x,y2) :- \n   as(y1, number) <= as(y2, number).;)_",iter, [&](){return rel_delete_leader_c04a5d036082e503->size();});
if(!(rel_leader_d565398e1ef92697->empty()) && !(rel_delta_leader_d4159f531d436f83->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_delete_leader_c04a5d036082e503_op_ctxt,rel_delete_leader_c04a5d036082e503->createContext());
CREATE_OP_CONTEXT(rel_delta_leader_d4159f531d436f83_op_ctxt,rel_delta_leader_d4159f531d436f83->createContext());
CREATE_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt,rel_leader_d565398e1ef92697->createContext());
for(const auto& env0 : *rel_leader_d565398e1ef92697) {
auto range = rel_delta_leader_d4159f531d436f83->lowerUpperRange_12(Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast(env0[1])}},Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_delta_leader_d4159f531d436f83_op_ctxt));
for(const auto& env1 : range) {
if( true) {
Tuple<RamDomain,2> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1])}};
rel_delete_leader_c04a5d036082e503->insert(tuple,READ_OP_CONTEXT(rel_delete_leader_c04a5d036082e503_op_ctxt));
break;
}
}
}
}
();}
}
[&](){
CREATE_OP_CONTEXT(rel_delete_leader_c04a5d036082e503_op_ctxt,rel_delete_leader_c04a5d036082e503->createContext());
for(const auto& env0 : *rel_delete_leader_c04a5d036082e503) {
Tuple<RamDomain,2> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1])}};
rel_leader_d565398e1ef92697->erase(tuple);
}
}
();rel_delete_leader_c04a5d036082e503->purge();
}
{
	Logger logger(R"_(@t-recursive-relation;var;subsumption.dl [9:7-9:10];)_",iter, [&](){return rel_new_var_7aacd8d7c9129d14->size();});
rel_delta_var_789565ec55b51a31->purge();
signalHandler->setMsg(R"_(var(x,c1) <= var(x,c2) :- 
   leader(c1,c2).
in file subsumption.dl [53:1-54:20])_");
{
	Logger logger(R"_(@t-recursive-rule;var;0;subsumption.dl [53:1-54:20];var(x,c1) <= var(x,c2) :- \n   leader(c1,c2).;)_",iter, [&](){return rel_reject_var_3661e6768640ec8b->size();});
if(!(rel_leader_d565398e1ef92697->empty()) && !(rel_new_var_7aacd8d7c9129d14->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_new_var_7aacd8d7c9129d14_op_ctxt,rel_new_var_7aacd8d7c9129d14->createContext());
CREATE_OP_CONTEXT(rel_reject_var_3661e6768640ec8b_op_ctxt,rel_reject_var_3661e6768640ec8b->createContext());
CREATE_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt,rel_leader_d565398e1ef92697->createContext());
for(const auto& env0 : *rel_new_var_7aacd8d7c9129d14) {
auto range = rel_new_var_7aacd8d7c9129d14->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_new_var_7aacd8d7c9129d14_op_ctxt));
for(const auto& env1 : range) {
if( !((ramBitCast<RamDomain>(env0[1]) == ramBitCast<RamDomain>(env1[1]))) && rel_leader_d565398e1ef92697->contains(Tuple<RamDomain,2>{{ramBitCast(env0[1]),ramBitCast(env1[1])}},READ_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt))) {
Tuple<RamDomain,2> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1])}};
rel_reject_var_3661e6768640ec8b->insert(tuple,READ_OP_CONTEXT(rel_reject_var_3661e6768640ec8b_op_ctxt));
}
}
}
}
();}
}
signalHandler->setMsg(R"_(var(x,c1) <= var(x,c2) :- 
   leader(c1,c2).
in file subsumption.dl [53:1-54:20])_");
{
	Logger logger(R"_(@t-recursive-rule;var;0;subsumption.dl [53:1-54:20];var(x,c1) <= var(x,c2) :- \n   leader(c1,c2).;)_",iter, [&](){return rel_reject_var_3661e6768640ec8b->size();});
if(!(rel_var_09870be8e1a4a08e->empty()) && !(rel_leader_d565398e1ef92697->empty()) && !(rel_new_var_7aacd8d7c9129d14->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_new_var_7aacd8d7c9129d14_op_ctxt,rel_new_var_7aacd8d7c9129d14->createContext());
CREATE_OP_CONTEXT(rel_reject_var_3661e6768640ec8b_op_ctxt,rel_reject_var_3661e6768640ec8b->createContext());
CREATE_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt,rel_leader_d565398e1ef92697->createContext());
CREATE_OP_CONTEXT(rel_var_09870be8e1a4a08e_op_ctxt,rel_var_09870be8e1a4a08e->createContext());
for(const auto& env0 : *rel_new_var_7aacd8d7c9129d14) {
auto range = rel_var_09870be8e1a4a08e->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_var_09870be8e1a4a08e_op_ctxt));
for(const auto& env1 : range) {
if( rel_leader_d565398e1ef92697->contains(Tuple<RamDomain,2>{{ramBitCast(env0[1]),ramBitCast(env1[1])}},READ_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt))) {
Tuple<RamDomain,2> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1])}};
rel_reject_var_3661e6768640ec8b->insert(tuple,READ_OP_CONTEXT(rel_reject_var_3661e6768640ec8b_op_ctxt));
break;
}
}
}
}
();}
}
signalHandler->setMsg(R"_(var(x,c1) <= var(x,c2) :- 
   leader(c1,c2).
in file subsumption.dl [53:1-54:20])_");
{
	Logger logger(R"_(@t-recursive-rule;var;1;subsumption.dl [53:1-54:20];var(x,c1) <= var(x,c2) :- \n   leader(c1,c2).;)_",iter, [&](){return rel_reject_var_3661e6768640ec8b->size();});
if(!(rel_delta_leader_d4159f531d436f83->empty()) && !(rel_new_var_7aacd8d7c9129d14->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_delta_leader_d4159f531d436f83_op_ctxt,rel_delta_leader_d4159f531d436f83->createContext());
CREATE_OP_CONTEXT(rel_new_var_7aacd8d7c9129d14_op_ctxt,rel_new_var_7aacd8d7c9129d14->createContext());
CREATE_OP_CONTEXT(rel_reject_var_3661e6768640ec8b_op_ctxt,rel_reject_var_3661e6768640ec8b->createContext());
for(const auto& env0 : *rel_new_var_7aacd8d7c9129d14) {
auto range = rel_new_var_7aacd8d7c9129d14->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_new_var_7aacd8d7c9129d14_op_ctxt));
for(const auto& env1 : range) {
if( !((ramBitCast<RamDomain>(env0[1]) == ramBitCast<RamDomain>(env1[1]))) && rel_delta_leader_d4159f531d436f83->contains(Tuple<RamDomain,2>{{ramBitCast(env0[1]),ramBitCast(env1[1])}},READ_OP_CONTEXT(rel_delta_leader_d4159f531d436f83_op_ctxt))) {
Tuple<RamDomain,2> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1])}};
rel_reject_var_3661e6768640ec8b->insert(tuple,READ_OP_CONTEXT(rel_reject_var_3661e6768640ec8b_op_ctxt));
}
}
}
}
();}
}
signalHandler->setMsg(R"_(var(x,c1) <= var(x,c2) :- 
   leader(c1,c2).
in file subsumption.dl [53:1-54:20])_");
{
	Logger logger(R"_(@t-recursive-rule;var;1;subsumption.dl [53:1-54:20];var(x,c1) <= var(x,c2) :- \n   leader(c1,c2).;)_",iter, [&](){return rel_reject_var_3661e6768640ec8b->size();});
if(!(rel_var_09870be8e1a4a08e->empty()) && !(rel_delta_leader_d4159f531d436f83->empty()) && !(rel_new_var_7aacd8d7c9129d14->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_delta_leader_d4159f531d436f83_op_ctxt,rel_delta_leader_d4159f531d436f83->createContext());
CREATE_OP_CONTEXT(rel_new_var_7aacd8d7c9129d14_op_ctxt,rel_new_var_7aacd8d7c9129d14->createContext());
CREATE_OP_CONTEXT(rel_reject_var_3661e6768640ec8b_op_ctxt,rel_reject_var_3661e6768640ec8b->createContext());
CREATE_OP_CONTEXT(rel_var_09870be8e1a4a08e_op_ctxt,rel_var_09870be8e1a4a08e->createContext());
for(const auto& env0 : *rel_new_var_7aacd8d7c9129d14) {
auto range = rel_var_09870be8e1a4a08e->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_var_09870be8e1a4a08e_op_ctxt));
for(const auto& env1 : range) {
if( rel_delta_leader_d4159f531d436f83->contains(Tuple<RamDomain,2>{{ramBitCast(env0[1]),ramBitCast(env1[1])}},READ_OP_CONTEXT(rel_delta_leader_d4159f531d436f83_op_ctxt))) {
Tuple<RamDomain,2> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1])}};
rel_reject_var_3661e6768640ec8b->insert(tuple,READ_OP_CONTEXT(rel_reject_var_3661e6768640ec8b_op_ctxt));
break;
}
}
}
}
();}
}
[&](){
CREATE_OP_CONTEXT(rel_delta_var_789565ec55b51a31_op_ctxt,rel_delta_var_789565ec55b51a31->createContext());
CREATE_OP_CONTEXT(rel_new_var_7aacd8d7c9129d14_op_ctxt,rel_new_var_7aacd8d7c9129d14->createContext());
CREATE_OP_CONTEXT(rel_reject_var_3661e6768640ec8b_op_ctxt,rel_reject_var_3661e6768640ec8b->createContext());
for(const auto& env0 : *rel_new_var_7aacd8d7c9129d14) {
if( !(rel_reject_var_3661e6768640ec8b->contains(Tuple<RamDomain,2>{{ramBitCast(env0[0]),ramBitCast(env0[1])}},READ_OP_CONTEXT(rel_reject_var_3661e6768640ec8b_op_ctxt)))) {
Tuple<RamDomain,2> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1])}};
rel_delta_var_789565ec55b51a31->insert(tuple,READ_OP_CONTEXT(rel_delta_var_789565ec55b51a31_op_ctxt));
}
}
}
();rel_reject_var_3661e6768640ec8b->purge();
rel_new_var_7aacd8d7c9129d14->purge();
signalHandler->setMsg(R"_(var(x,c1) <= var(x,c2) :- 
   leader(c1,c2).
in file subsumption.dl [53:1-54:20])_");
{
	Logger logger(R"_(@t-recursive-rule;var;0;subsumption.dl [53:1-54:20];var(x,c1) <= var(x,c2) :- \n   leader(c1,c2).;)_",iter, [&](){return rel_delete_var_73e06489152dbaa5->size();});
if(!(rel_leader_d565398e1ef92697->empty()) && !(rel_var_09870be8e1a4a08e->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_delete_var_73e06489152dbaa5_op_ctxt,rel_delete_var_73e06489152dbaa5->createContext());
CREATE_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt,rel_leader_d565398e1ef92697->createContext());
CREATE_OP_CONTEXT(rel_var_09870be8e1a4a08e_op_ctxt,rel_var_09870be8e1a4a08e->createContext());
for(const auto& env0 : *rel_var_09870be8e1a4a08e) {
auto range = rel_var_09870be8e1a4a08e->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_var_09870be8e1a4a08e_op_ctxt));
for(const auto& env1 : range) {
if( !((ramBitCast<RamDomain>(env0[1]) == ramBitCast<RamDomain>(env1[1]))) && rel_leader_d565398e1ef92697->contains(Tuple<RamDomain,2>{{ramBitCast(env0[1]),ramBitCast(env1[1])}},READ_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt))) {
Tuple<RamDomain,2> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1])}};
rel_delete_var_73e06489152dbaa5->insert(tuple,READ_OP_CONTEXT(rel_delete_var_73e06489152dbaa5_op_ctxt));
}
}
}
}
();}
}
signalHandler->setMsg(R"_(var(x,c1) <= var(x,c2) :- 
   leader(c1,c2).
in file subsumption.dl [53:1-54:20])_");
{
	Logger logger(R"_(@t-recursive-rule;var;1;subsumption.dl [53:1-54:20];var(x,c1) <= var(x,c2) :- \n   leader(c1,c2).;)_",iter, [&](){return rel_delete_var_73e06489152dbaa5->size();});
if(!(rel_delta_leader_d4159f531d436f83->empty()) && !(rel_var_09870be8e1a4a08e->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_delete_var_73e06489152dbaa5_op_ctxt,rel_delete_var_73e06489152dbaa5->createContext());
CREATE_OP_CONTEXT(rel_delta_leader_d4159f531d436f83_op_ctxt,rel_delta_leader_d4159f531d436f83->createContext());
CREATE_OP_CONTEXT(rel_var_09870be8e1a4a08e_op_ctxt,rel_var_09870be8e1a4a08e->createContext());
for(const auto& env0 : *rel_var_09870be8e1a4a08e) {
auto range = rel_var_09870be8e1a4a08e->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[0]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_var_09870be8e1a4a08e_op_ctxt));
for(const auto& env1 : range) {
if( !((ramBitCast<RamDomain>(env0[1]) == ramBitCast<RamDomain>(env1[1]))) && rel_delta_leader_d4159f531d436f83->contains(Tuple<RamDomain,2>{{ramBitCast(env0[1]),ramBitCast(env1[1])}},READ_OP_CONTEXT(rel_delta_leader_d4159f531d436f83_op_ctxt))) {
Tuple<RamDomain,2> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1])}};
rel_delete_var_73e06489152dbaa5->insert(tuple,READ_OP_CONTEXT(rel_delete_var_73e06489152dbaa5_op_ctxt));
}
}
}
}
();}
}
[&](){
CREATE_OP_CONTEXT(rel_delete_var_73e06489152dbaa5_op_ctxt,rel_delete_var_73e06489152dbaa5->createContext());
for(const auto& env0 : *rel_delete_var_73e06489152dbaa5) {
Tuple<RamDomain,2> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1])}};
rel_var_09870be8e1a4a08e->erase(tuple);
}
}
();rel_delete_var_73e06489152dbaa5->purge();
}
if(rel_delta_add_241d705dc2fb23df->empty() && rel_new_eql_10ebb01129546352->empty() && rel_delta_leader_d4159f531d436f83->empty() && rel_delta_var_789565ec55b51a31->empty()) break;
{
	Logger logger(R"_(@c-recursive-relation;add;subsumption.dl [8:7-8:10];)_",iter, [&](){return rel_new_add_954a8c50e586f068->size();});
[&](){
CREATE_OP_CONTEXT(rel_delta_add_241d705dc2fb23df_op_ctxt,rel_delta_add_241d705dc2fb23df->createContext());
CREATE_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt,rel_add_48c57da858454f79->createContext());
for(const auto& env0 : *rel_delta_add_241d705dc2fb23df) {
Tuple<RamDomain,3> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1]),ramBitCast(env0[2])}};
rel_add_48c57da858454f79->insert(tuple,READ_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt));
}
}
();}
{
	Logger logger(R"_(@c-recursive-relation;eql;subsumption.dl [7:7-7:10];)_",iter, [&](){return rel_new_eql_10ebb01129546352->size();});
rel_new_eql_10ebb01129546352->extendAndInsert(*rel_eql_e1be027843ac9bc5);
std::swap(rel_delta_eql_fdc75db4daac3372, rel_new_eql_10ebb01129546352);
rel_new_eql_10ebb01129546352->purge();
}
{
	Logger logger(R"_(@c-recursive-relation;leader;subsumption.dl [57:7-57:13];)_",iter, [&](){return rel_new_leader_99e6be51e44547e4->size();});
[&](){
CREATE_OP_CONTEXT(rel_delta_leader_d4159f531d436f83_op_ctxt,rel_delta_leader_d4159f531d436f83->createContext());
CREATE_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt,rel_leader_d565398e1ef92697->createContext());
for(const auto& env0 : *rel_delta_leader_d4159f531d436f83) {
Tuple<RamDomain,2> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1])}};
rel_leader_d565398e1ef92697->insert(tuple,READ_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt));
}
}
();}
{
	Logger logger(R"_(@c-recursive-relation;var;subsumption.dl [9:7-9:10];)_",iter, [&](){return rel_new_var_7aacd8d7c9129d14->size();});
[&](){
CREATE_OP_CONTEXT(rel_delta_var_789565ec55b51a31_op_ctxt,rel_delta_var_789565ec55b51a31->createContext());
CREATE_OP_CONTEXT(rel_var_09870be8e1a4a08e_op_ctxt,rel_var_09870be8e1a4a08e->createContext());
for(const auto& env0 : *rel_delta_var_789565ec55b51a31) {
Tuple<RamDomain,2> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1])}};
rel_var_09870be8e1a4a08e->insert(tuple,READ_OP_CONTEXT(rel_var_09870be8e1a4a08e_op_ctxt));
}
}
();}
iter++;
}
iter = 0;
rel_delta_add_241d705dc2fb23df->purge();
rel_new_add_954a8c50e586f068->purge();
rel_delta_eql_fdc75db4daac3372->purge();
rel_new_eql_10ebb01129546352->purge();
rel_delta_leader_d4159f531d436f83->purge();
rel_new_leader_99e6be51e44547e4->purge();
rel_delta_var_789565ec55b51a31->purge();
rel_new_var_7aacd8d7c9129d14->purge();
{
	Logger logger(R"_(@t-relation-savetime;leader;subsumption.dl [57:7-57:13];savetime;)_",iter, [&](){return rel_leader_d565398e1ef92697->size();});
if (performIO) {
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","a\tb"},{"auxArity","0"},{"name","leader"},{"operation","output"},{"output-dir","subsumption"},{"params","{\"records\": {}, \"relation\": {\"arity\": 2, \"params\": [\"a\", \"b\"]}}"},{"types","{\"ADTs\": {\"+:Id\": {\"arity\": 2, \"branches\": [{\"name\": \"Add\", \"types\": [\"+:Id\", \"+:Id\"]}, {\"name\": \"Var\", \"types\": [\"i:number\"]}], \"enum\": false}}, \"records\": {}, \"relation\": {\"arity\": 2, \"types\": [\"+:Id\", \"+:Id\"]}}"}});
if (!outputDirectory.empty()) {directiveMap["output-dir"] = outputDirectory;}
IOSystem::getInstance().getWriter(directiveMap, symTable, recordTable)->writeAll(*rel_leader_d565398e1ef92697);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
}
}
if (pruneImdtRels) rel_N_913bf6e156bb077c->purge();
if (pruneImdtRels) rel_add_prep_e8dfec160429ed9e->purge();
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
{
	Logger logger(R"_(@t-nonrecursive-relation;add_prep;subsumption.dl [11:7-11:15];)_",iter, [&](){return rel_add_prep_e8dfec160429ed9e->size();});
signalHandler->setMsg(R"_(add_prep($Var(2),$Var(1),$Add($Var(2), $Var(1))).
in file subsumption.dl [14:1-14:52])_");
{
	Logger logger(R"_(@t-nonrecursive-rule;add_prep;subsumption.dl [14:1-14:52];add_prep($Var(2),$Var(1),$Add($Var(2), $Var(1))).;)_",iter, [&](){return rel_add_prep_e8dfec160429ed9e->size();});
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
();}
}
[&](){
CREATE_OP_CONTEXT(rel_delta_add_prep_81473cce7460e2b6_op_ctxt,rel_delta_add_prep_81473cce7460e2b6->createContext());
CREATE_OP_CONTEXT(rel_add_prep_e8dfec160429ed9e_op_ctxt,rel_add_prep_e8dfec160429ed9e->createContext());
for(const auto& env0 : *rel_add_prep_e8dfec160429ed9e) {
Tuple<RamDomain,3> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1]),ramBitCast(env0[2])}};
rel_delta_add_prep_81473cce7460e2b6->insert(tuple,READ_OP_CONTEXT(rel_delta_add_prep_81473cce7460e2b6_op_ctxt));
}
}
();iter = 0;
for(;;) {
{
	Logger logger(R"_(@t-recursive-relation;add_prep;subsumption.dl [11:7-11:15];)_",iter, [&](){return rel_new_add_prep_d729e5114de538fd->size();});
signalHandler->setMsg(R"_(add_prep($Var((x+1)),id,$Add($Var((x+1)), id)) :- 
   add_prep($Var(x),_,id),
   x <= n,
   N(n).
in file subsumption.dl [15:1-19:15])_");
{
	Logger logger(R"_(@t-recursive-rule;add_prep;0;subsumption.dl [15:1-19:15];add_prep($Var((x+1)),id,$Add($Var((x+1)), id)) :- \n   add_prep($Var(x),_,id),\n   x <= n,\n   N(n).;)_",iter, [&](){return rel_new_add_prep_d729e5114de538fd->size();});
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
}
}
{
	Logger logger(R"_(@t-recursive-relation;add_prep;subsumption.dl [11:7-11:15];)_",iter, [&](){return rel_new_add_prep_d729e5114de538fd->size();});
}
if(rel_new_add_prep_d729e5114de538fd->empty()) break;
{
	Logger logger(R"_(@c-recursive-relation;add_prep;subsumption.dl [11:7-11:15];)_",iter, [&](){return rel_new_add_prep_d729e5114de538fd->size();});
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
}
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
 Stratum_class_7ad9e07ae9eb30e9(SymbolTable& symTable,RecordTable& recordTable,bool& pruneImdtRels,bool& performIO,SignalHandler*& signalHandler,std::atomic<std::size_t>& iter,std::atomic<RamDomain>& ctr,std::string& inputDirectory,std::string& outputDirectory,t_btree_i__0__1::Type& rel_class_9017e5267072d9ea,t_eqrel& rel_eql_e1be027843ac9bc5);
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
t_eqrel* rel_eql_e1be027843ac9bc5;
};
} // namespace souffle
namespace souffle {
 Stratum_class_7ad9e07ae9eb30e9::Stratum_class_7ad9e07ae9eb30e9(SymbolTable& symTable,RecordTable& recordTable,bool& pruneImdtRels,bool& performIO,SignalHandler*& signalHandler,std::atomic<std::size_t>& iter,std::atomic<RamDomain>& ctr,std::string& inputDirectory,std::string& outputDirectory,t_btree_i__0__1::Type& rel_class_9017e5267072d9ea,t_eqrel& rel_eql_e1be027843ac9bc5):
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
rel_eql_e1be027843ac9bc5(&rel_eql_e1be027843ac9bc5){
}

void Stratum_class_7ad9e07ae9eb30e9::run([[maybe_unused]] const std::vector<RamDomain>& args,[[maybe_unused]] std::vector<RamDomain>& ret){
{
	Logger logger(R"_(@t-nonrecursive-relation;class;subsumption.dl [62:7-62:12];)_",iter, [&](){return rel_class_9017e5267072d9ea->size();});
signalHandler->setMsg(R"_(class(as(@generator_0, Id)) :- 
   eql(a,a),
   @generator_0 = min as(b0, number) : { eql(a,b0),as(b0, number) = as(b0, number) }.
in file subsumption.dl [63:1-63:79])_");
{
	Logger logger(R"_(@t-nonrecursive-rule;class;subsumption.dl [63:1-63:79];class(as(@generator_0, Id)) :- \n   eql(a,a),\n   @generator_0 = min as(b0, number) : { eql(a,b0),as(b0, number) = as(b0, number) }.;)_",iter, [&](){return rel_class_9017e5267072d9ea->size();});
if(!(rel_eql_e1be027843ac9bc5->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_class_9017e5267072d9ea_op_ctxt,rel_class_9017e5267072d9ea->createContext());
CREATE_OP_CONTEXT(rel_eql_e1be027843ac9bc5_op_ctxt,rel_eql_e1be027843ac9bc5->createContext());
for(const auto& env0 : *rel_eql_e1be027843ac9bc5) {
if( (ramBitCast<RamDomain>(env0[0]) == ramBitCast<RamDomain>(env0[1]))) {
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
Tuple<RamDomain,1> tuple{{ramBitCast(env1[0])}};
rel_class_9017e5267072d9ea->insert(tuple,READ_OP_CONTEXT(rel_class_9017e5267072d9ea_op_ctxt));
}
}
}
}
}
();}
}
}
{
	Logger logger(R"_(@t-relation-savetime;class;subsumption.dl [62:7-62:12];savetime;)_",iter, [&](){return rel_class_9017e5267072d9ea->size();});
if (performIO) {
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","a"},{"auxArity","0"},{"name","class"},{"operation","output"},{"output-dir","subsumption"},{"params","{\"records\": {}, \"relation\": {\"arity\": 1, \"params\": [\"a\"]}}"},{"types","{\"ADTs\": {\"+:Id\": {\"arity\": 2, \"branches\": [{\"name\": \"Add\", \"types\": [\"+:Id\", \"+:Id\"]}, {\"name\": \"Var\", \"types\": [\"i:number\"]}], \"enum\": false}}, \"records\": {}, \"relation\": {\"arity\": 1, \"types\": [\"+:Id\"]}}"}});
if (!outputDirectory.empty()) {directiveMap["output-dir"] = outputDirectory;}
IOSystem::getInstance().getWriter(directiveMap, symTable, recordTable)->writeAll(*rel_class_9017e5267072d9ea);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
}
}
if (pruneImdtRels) rel_eql_e1be027843ac9bc5->purge();
}

} // namespace souffle

namespace souffle {
class Stratum_root_83915ac4426ff1c9 {
public:
 Stratum_root_83915ac4426ff1c9(SymbolTable& symTable,RecordTable& recordTable,bool& pruneImdtRels,bool& performIO,SignalHandler*& signalHandler,std::atomic<std::size_t>& iter,std::atomic<RamDomain>& ctr,std::string& inputDirectory,std::string& outputDirectory,t_btree_delete_iii__0_1_2__100__110__111::Type& rel_add_48c57da858454f79,t_btree_delete_ii__0_1__11__12__10::Type& rel_leader_d565398e1ef92697,t_btree_ii__0_1__11::Type& rel_root_4971aadef59ffd68,t_btree_delete_ii__0_1__11__10::Type& rel_var_09870be8e1a4a08e);
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
t_btree_delete_iii__0_1_2__100__110__111::Type* rel_add_48c57da858454f79;
t_btree_delete_ii__0_1__11__12__10::Type* rel_leader_d565398e1ef92697;
t_btree_ii__0_1__11::Type* rel_root_4971aadef59ffd68;
t_btree_delete_ii__0_1__11__10::Type* rel_var_09870be8e1a4a08e;
};
} // namespace souffle
namespace souffle {
 Stratum_root_83915ac4426ff1c9::Stratum_root_83915ac4426ff1c9(SymbolTable& symTable,RecordTable& recordTable,bool& pruneImdtRels,bool& performIO,SignalHandler*& signalHandler,std::atomic<std::size_t>& iter,std::atomic<RamDomain>& ctr,std::string& inputDirectory,std::string& outputDirectory,t_btree_delete_iii__0_1_2__100__110__111::Type& rel_add_48c57da858454f79,t_btree_delete_ii__0_1__11__12__10::Type& rel_leader_d565398e1ef92697,t_btree_ii__0_1__11::Type& rel_root_4971aadef59ffd68,t_btree_delete_ii__0_1__11__10::Type& rel_var_09870be8e1a4a08e):
symTable(symTable),
recordTable(recordTable),
pruneImdtRels(pruneImdtRels),
performIO(performIO),
signalHandler(signalHandler),
iter(iter),
ctr(ctr),
inputDirectory(inputDirectory),
outputDirectory(outputDirectory),
rel_add_48c57da858454f79(&rel_add_48c57da858454f79),
rel_leader_d565398e1ef92697(&rel_leader_d565398e1ef92697),
rel_root_4971aadef59ffd68(&rel_root_4971aadef59ffd68),
rel_var_09870be8e1a4a08e(&rel_var_09870be8e1a4a08e){
}

void Stratum_root_83915ac4426ff1c9::run([[maybe_unused]] const std::vector<RamDomain>& args,[[maybe_unused]] std::vector<RamDomain>& ret){
{
	Logger logger(R"_(@t-nonrecursive-relation;root;subsumption.dl [65:7-65:11];)_",iter, [&](){return rel_root_4971aadef59ffd68->size();});
signalHandler->setMsg(R"_(root(1,lx1234) :- 
   var(1,x1),
   leader(x1,lx1),
   var(2,x2),
   leader(x2,lx2),
   var(3,x3),
   leader(x3,lx3),
   var(4,x4),
   leader(x4,lx4),
   add(lx1,lx2,x12),
   leader(x12,lx12),
   add(lx12,lx3,x123),
   leader(x123,lx123),
   add(lx123,lx4,x1234),
   leader(x1234,lx1234).
in file subsumption.dl [67:1-74:51])_");
{
	Logger logger(R"_(@t-nonrecursive-rule;root;subsumption.dl [67:1-74:51];root(1,lx1234) :- \n   var(1,x1),\n   leader(x1,lx1),\n   var(2,x2),\n   leader(x2,lx2),\n   var(3,x3),\n   leader(x3,lx3),\n   var(4,x4),\n   leader(x4,lx4),\n   add(lx1,lx2,x12),\n   leader(x12,lx12),\n   add(lx12,lx3,x123),\n   leader(x123,lx123),\n   add(lx123,lx4,x1234),\n   leader(x1234,lx1234).;)_",iter, [&](){return rel_root_4971aadef59ffd68->size();});
if(!(rel_add_48c57da858454f79->empty()) && !(rel_var_09870be8e1a4a08e->empty()) && !(rel_leader_d565398e1ef92697->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt,rel_add_48c57da858454f79->createContext());
CREATE_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt,rel_leader_d565398e1ef92697->createContext());
CREATE_OP_CONTEXT(rel_root_4971aadef59ffd68_op_ctxt,rel_root_4971aadef59ffd68->createContext());
CREATE_OP_CONTEXT(rel_var_09870be8e1a4a08e_op_ctxt,rel_var_09870be8e1a4a08e->createContext());
auto range = rel_var_09870be8e1a4a08e->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(RamSigned(1)), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(RamSigned(1)), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_var_09870be8e1a4a08e_op_ctxt));
for(const auto& env0 : range) {
auto range = rel_leader_d565398e1ef92697->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt));
for(const auto& env1 : range) {
auto range = rel_var_09870be8e1a4a08e->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(RamSigned(2)), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(RamSigned(2)), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_var_09870be8e1a4a08e_op_ctxt));
for(const auto& env2 : range) {
auto range = rel_leader_d565398e1ef92697->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env2[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env2[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt));
for(const auto& env3 : range) {
auto range = rel_var_09870be8e1a4a08e->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(RamSigned(3)), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(RamSigned(3)), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_var_09870be8e1a4a08e_op_ctxt));
for(const auto& env4 : range) {
auto range = rel_leader_d565398e1ef92697->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env4[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env4[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt));
for(const auto& env5 : range) {
auto range = rel_var_09870be8e1a4a08e->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(RamSigned(4)), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(RamSigned(4)), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_var_09870be8e1a4a08e_op_ctxt));
for(const auto& env6 : range) {
auto range = rel_leader_d565398e1ef92697->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env6[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env6[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt));
for(const auto& env7 : range) {
auto range = rel_add_48c57da858454f79->lowerUpperRange_110(Tuple<RamDomain,3>{{ramBitCast(env1[1]), ramBitCast(env3[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,3>{{ramBitCast(env1[1]), ramBitCast(env3[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt));
for(const auto& env8 : range) {
auto range = rel_leader_d565398e1ef92697->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env8[2]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env8[2]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt));
for(const auto& env9 : range) {
auto range = rel_add_48c57da858454f79->lowerUpperRange_110(Tuple<RamDomain,3>{{ramBitCast(env9[1]), ramBitCast(env5[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,3>{{ramBitCast(env9[1]), ramBitCast(env5[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt));
for(const auto& env10 : range) {
auto range = rel_leader_d565398e1ef92697->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env10[2]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env10[2]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt));
for(const auto& env11 : range) {
auto range = rel_add_48c57da858454f79->lowerUpperRange_110(Tuple<RamDomain,3>{{ramBitCast(env11[1]), ramBitCast(env7[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,3>{{ramBitCast(env11[1]), ramBitCast(env7[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt));
for(const auto& env12 : range) {
auto range = rel_leader_d565398e1ef92697->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env12[2]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env12[2]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt));
for(const auto& env13 : range) {
Tuple<RamDomain,2> tuple{{ramBitCast(RamSigned(1)),ramBitCast(env13[1])}};
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
();}
}
signalHandler->setMsg(R"_(root(2,lx4321) :- 
   var(1,x1),
   leader(x1,lx1),
   var(2,x2),
   leader(x2,lx2),
   var(3,x3),
   leader(x3,lx3),
   var(4,x4),
   leader(x4,lx4),
   add(lx4,lx3,x43),
   leader(x43,lx43),
   add(lx43,lx2,x432),
   leader(x432,lx432),
   add(lx432,lx1,x4321),
   leader(x4321,lx4321).
in file subsumption.dl [77:1-84:51])_");
{
	Logger logger(R"_(@t-nonrecursive-rule;root;subsumption.dl [77:1-84:51];root(2,lx4321) :- \n   var(1,x1),\n   leader(x1,lx1),\n   var(2,x2),\n   leader(x2,lx2),\n   var(3,x3),\n   leader(x3,lx3),\n   var(4,x4),\n   leader(x4,lx4),\n   add(lx4,lx3,x43),\n   leader(x43,lx43),\n   add(lx43,lx2,x432),\n   leader(x432,lx432),\n   add(lx432,lx1,x4321),\n   leader(x4321,lx4321).;)_",iter, [&](){return rel_root_4971aadef59ffd68->size();});
if(!(rel_add_48c57da858454f79->empty()) && !(rel_var_09870be8e1a4a08e->empty()) && !(rel_leader_d565398e1ef92697->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt,rel_add_48c57da858454f79->createContext());
CREATE_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt,rel_leader_d565398e1ef92697->createContext());
CREATE_OP_CONTEXT(rel_root_4971aadef59ffd68_op_ctxt,rel_root_4971aadef59ffd68->createContext());
CREATE_OP_CONTEXT(rel_var_09870be8e1a4a08e_op_ctxt,rel_var_09870be8e1a4a08e->createContext());
auto range = rel_var_09870be8e1a4a08e->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(RamSigned(1)), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(RamSigned(1)), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_var_09870be8e1a4a08e_op_ctxt));
for(const auto& env0 : range) {
auto range = rel_leader_d565398e1ef92697->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt));
for(const auto& env1 : range) {
auto range = rel_var_09870be8e1a4a08e->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(RamSigned(2)), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(RamSigned(2)), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_var_09870be8e1a4a08e_op_ctxt));
for(const auto& env2 : range) {
auto range = rel_leader_d565398e1ef92697->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env2[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env2[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt));
for(const auto& env3 : range) {
auto range = rel_var_09870be8e1a4a08e->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(RamSigned(3)), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(RamSigned(3)), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_var_09870be8e1a4a08e_op_ctxt));
for(const auto& env4 : range) {
auto range = rel_leader_d565398e1ef92697->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env4[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env4[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt));
for(const auto& env5 : range) {
auto range = rel_var_09870be8e1a4a08e->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(RamSigned(4)), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(RamSigned(4)), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_var_09870be8e1a4a08e_op_ctxt));
for(const auto& env6 : range) {
auto range = rel_leader_d565398e1ef92697->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env6[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env6[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt));
for(const auto& env7 : range) {
auto range = rel_add_48c57da858454f79->lowerUpperRange_110(Tuple<RamDomain,3>{{ramBitCast(env7[1]), ramBitCast(env5[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,3>{{ramBitCast(env7[1]), ramBitCast(env5[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt));
for(const auto& env8 : range) {
auto range = rel_leader_d565398e1ef92697->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env8[2]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env8[2]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt));
for(const auto& env9 : range) {
auto range = rel_add_48c57da858454f79->lowerUpperRange_110(Tuple<RamDomain,3>{{ramBitCast(env9[1]), ramBitCast(env3[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,3>{{ramBitCast(env9[1]), ramBitCast(env3[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt));
for(const auto& env10 : range) {
auto range = rel_leader_d565398e1ef92697->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env10[2]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env10[2]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt));
for(const auto& env11 : range) {
auto range = rel_add_48c57da858454f79->lowerUpperRange_110(Tuple<RamDomain,3>{{ramBitCast(env11[1]), ramBitCast(env1[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,3>{{ramBitCast(env11[1]), ramBitCast(env1[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_add_48c57da858454f79_op_ctxt));
for(const auto& env12 : range) {
auto range = rel_leader_d565398e1ef92697->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env12[2]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env12[2]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_leader_d565398e1ef92697_op_ctxt));
for(const auto& env13 : range) {
Tuple<RamDomain,2> tuple{{ramBitCast(RamSigned(2)),ramBitCast(env13[1])}};
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
();}
}
}
{
	Logger logger(R"_(@t-relation-savetime;root;subsumption.dl [65:7-65:11];savetime;)_",iter, [&](){return rel_root_4971aadef59ffd68->size();});
if (performIO) {
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","i\ta"},{"auxArity","0"},{"name","root"},{"operation","output"},{"output-dir","subsumption"},{"params","{\"records\": {}, \"relation\": {\"arity\": 2, \"params\": [\"i\", \"a\"]}}"},{"types","{\"ADTs\": {\"+:Id\": {\"arity\": 2, \"branches\": [{\"name\": \"Add\", \"types\": [\"+:Id\", \"+:Id\"]}, {\"name\": \"Var\", \"types\": [\"i:number\"]}], \"enum\": false}}, \"records\": {}, \"relation\": {\"arity\": 2, \"types\": [\"i:number\", \"+:Id\"]}}"}});
if (!outputDirectory.empty()) {directiveMap["output-dir"] = outputDirectory;}
IOSystem::getInstance().getWriter(directiveMap, symTable, recordTable)->writeAll(*rel_root_4971aadef59ffd68);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
}
}
if (pruneImdtRels) rel_add_48c57da858454f79->purge();
if (pruneImdtRels) rel_leader_d565398e1ef92697->purge();
if (pruneImdtRels) rel_var_09870be8e1a4a08e->purge();
}

} // namespace souffle

namespace souffle {
class Sf_subsumption: public SouffleProgram {
public:
 Sf_subsumption(std::string pf = "profile.log");
 ~Sf_subsumption();
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
std::string profiling_fname;
private:
void runFunction(std::string inputDirectoryArg,std::string outputDirectoryArg,bool performIOArg,bool pruneImdtRelsArg);
void dumpFreqs();
SymbolTableImpl symTable;
SpecializedRecordTable<0,2> recordTable;
std::size_t freqs[394];
std::size_t reads[8];
Own<t_btree_i__0__2__1::Type> rel_N_913bf6e156bb077c;
souffle::RelationWrapper<t_btree_i__0__2__1::Type> wrapper_rel_N_913bf6e156bb077c;
Own<t_btree_iii__0_1_2__111::Type> rel_add_prep_e8dfec160429ed9e;
souffle::RelationWrapper<t_btree_iii__0_1_2__111::Type> wrapper_rel_add_prep_e8dfec160429ed9e;
Own<t_btree_iii__0_1_2__111::Type> rel_delta_add_prep_81473cce7460e2b6;
Own<t_btree_iii__0_1_2__111::Type> rel_new_add_prep_d729e5114de538fd;
Own<t_btree_delete_iii__0_1_2__100__110__111::Type> rel_add_48c57da858454f79;
souffle::RelationWrapper<t_btree_delete_iii__0_1_2__100__110__111::Type> wrapper_rel_add_48c57da858454f79;
Own<t_btree_iii__0_1_2__100__110__111::Type> rel_delta_add_241d705dc2fb23df;
Own<t_btree_iii__0_1_2__111::Type> rel_new_add_954a8c50e586f068;
Own<t_btree_iii__0_1_2__111::Type> rel_reject_add_d8fb12f9ecd20122;
Own<t_btree_iii__0_1_2__111::Type> rel_delete_add_6fd868847292dbea;
Own<t_eqrel> rel_eql_e1be027843ac9bc5;
souffle::RelationWrapper<t_eqrel> wrapper_rel_eql_e1be027843ac9bc5;
Own<t_eqrel> rel_delta_eql_fdc75db4daac3372;
Own<t_eqrel> rel_new_eql_10ebb01129546352;
Own<t_btree_delete_ii__0_1__11__12__10::Type> rel_leader_d565398e1ef92697;
souffle::RelationWrapper<t_btree_delete_ii__0_1__11__12__10::Type> wrapper_rel_leader_d565398e1ef92697;
Own<t_btree_ii__0_1__11__12__10::Type> rel_delta_leader_d4159f531d436f83;
Own<t_btree_ii__0_1__11__12::Type> rel_new_leader_99e6be51e44547e4;
Own<t_btree_ii__0_1__11::Type> rel_reject_leader_c121991f9eab43a8;
Own<t_btree_ii__0_1__11::Type> rel_delete_leader_c04a5d036082e503;
Own<t_btree_delete_ii__0_1__11__10::Type> rel_var_09870be8e1a4a08e;
souffle::RelationWrapper<t_btree_delete_ii__0_1__11__10::Type> wrapper_rel_var_09870be8e1a4a08e;
Own<t_btree_ii__0_1__11__10::Type> rel_delta_var_789565ec55b51a31;
Own<t_btree_ii__0_1__11__10::Type> rel_new_var_7aacd8d7c9129d14;
Own<t_btree_ii__0_1__11::Type> rel_reject_var_3661e6768640ec8b;
Own<t_btree_ii__0_1__11::Type> rel_delete_var_73e06489152dbaa5;
Own<t_btree_i__0__1::Type> rel_class_9017e5267072d9ea;
souffle::RelationWrapper<t_btree_i__0__1::Type> wrapper_rel_class_9017e5267072d9ea;
Own<t_btree_ii__0_1__11::Type> rel_root_4971aadef59ffd68;
souffle::RelationWrapper<t_btree_ii__0_1__11::Type> wrapper_rel_root_4971aadef59ffd68;
Stratum_N_2fa3d15dc185d227 stratum_N_f2fd84e3ee54ddcf;
Stratum_add_ed981d530a6b23bd stratum_add_14722fa4ca06c6d9;
Stratum_add_prep_670e12a5611ce0c6 stratum_add_prep_ad75c73511997080;
Stratum_class_7ad9e07ae9eb30e9 stratum_class_a21f43f864200ec6;
Stratum_root_83915ac4426ff1c9 stratum_root_97ddb9257bc55be8;
std::string inputDirectory;
std::string outputDirectory;
SignalHandler* signalHandler{SignalHandler::instance()};
std::atomic<RamDomain> ctr{};
std::atomic<std::size_t> iter{};
};
} // namespace souffle
namespace souffle {
 Sf_subsumption::Sf_subsumption(std::string pf):
profiling_fname(std::move(pf)),
symTable(),
recordTable(),
freqs(),
reads(),
rel_N_913bf6e156bb077c(mk<t_btree_i__0__2__1::Type>()),
wrapper_rel_N_913bf6e156bb077c(0, *rel_N_913bf6e156bb077c, *this, "N", std::array<const char *,1>{{"i:number"}}, std::array<const char *,1>{{"n"}}, 0),
rel_add_prep_e8dfec160429ed9e(mk<t_btree_iii__0_1_2__111::Type>()),
wrapper_rel_add_prep_e8dfec160429ed9e(1, *rel_add_prep_e8dfec160429ed9e, *this, "add_prep", std::array<const char *,3>{{"+:Id","+:Id","+:Id"}}, std::array<const char *,3>{{"x","y","c"}}, 0),
rel_delta_add_prep_81473cce7460e2b6(mk<t_btree_iii__0_1_2__111::Type>()),
rel_new_add_prep_d729e5114de538fd(mk<t_btree_iii__0_1_2__111::Type>()),
rel_add_48c57da858454f79(mk<t_btree_delete_iii__0_1_2__100__110__111::Type>()),
wrapper_rel_add_48c57da858454f79(2, *rel_add_48c57da858454f79, *this, "add", std::array<const char *,3>{{"+:Id","+:Id","+:Id"}}, std::array<const char *,3>{{"x","y","c"}}, 0),
rel_delta_add_241d705dc2fb23df(mk<t_btree_iii__0_1_2__100__110__111::Type>()),
rel_new_add_954a8c50e586f068(mk<t_btree_iii__0_1_2__111::Type>()),
rel_reject_add_d8fb12f9ecd20122(mk<t_btree_iii__0_1_2__111::Type>()),
rel_delete_add_6fd868847292dbea(mk<t_btree_iii__0_1_2__111::Type>()),
rel_eql_e1be027843ac9bc5(mk<t_eqrel>()),
wrapper_rel_eql_e1be027843ac9bc5(3, *rel_eql_e1be027843ac9bc5, *this, "eql", std::array<const char *,2>{{"+:Id","+:Id"}}, std::array<const char *,2>{{"x","y"}}, 0),
rel_delta_eql_fdc75db4daac3372(mk<t_eqrel>()),
rel_new_eql_10ebb01129546352(mk<t_eqrel>()),
rel_leader_d565398e1ef92697(mk<t_btree_delete_ii__0_1__11__12__10::Type>()),
wrapper_rel_leader_d565398e1ef92697(4, *rel_leader_d565398e1ef92697, *this, "leader", std::array<const char *,2>{{"+:Id","+:Id"}}, std::array<const char *,2>{{"a","b"}}, 0),
rel_delta_leader_d4159f531d436f83(mk<t_btree_ii__0_1__11__12__10::Type>()),
rel_new_leader_99e6be51e44547e4(mk<t_btree_ii__0_1__11__12::Type>()),
rel_reject_leader_c121991f9eab43a8(mk<t_btree_ii__0_1__11::Type>()),
rel_delete_leader_c04a5d036082e503(mk<t_btree_ii__0_1__11::Type>()),
rel_var_09870be8e1a4a08e(mk<t_btree_delete_ii__0_1__11__10::Type>()),
wrapper_rel_var_09870be8e1a4a08e(5, *rel_var_09870be8e1a4a08e, *this, "var", std::array<const char *,2>{{"i:number","+:Id"}}, std::array<const char *,2>{{"x","c"}}, 0),
rel_delta_var_789565ec55b51a31(mk<t_btree_ii__0_1__11__10::Type>()),
rel_new_var_7aacd8d7c9129d14(mk<t_btree_ii__0_1__11__10::Type>()),
rel_reject_var_3661e6768640ec8b(mk<t_btree_ii__0_1__11::Type>()),
rel_delete_var_73e06489152dbaa5(mk<t_btree_ii__0_1__11::Type>()),
rel_class_9017e5267072d9ea(mk<t_btree_i__0__1::Type>()),
wrapper_rel_class_9017e5267072d9ea(6, *rel_class_9017e5267072d9ea, *this, "class", std::array<const char *,1>{{"+:Id"}}, std::array<const char *,1>{{"a"}}, 0),
rel_root_4971aadef59ffd68(mk<t_btree_ii__0_1__11::Type>()),
wrapper_rel_root_4971aadef59ffd68(7, *rel_root_4971aadef59ffd68, *this, "root", std::array<const char *,2>{{"i:number","+:Id"}}, std::array<const char *,2>{{"i","a"}}, 0),
stratum_N_f2fd84e3ee54ddcf(symTable,recordTable,pruneImdtRels,performIO,signalHandler,iter,ctr,inputDirectory,outputDirectory,*rel_N_913bf6e156bb077c),
stratum_add_14722fa4ca06c6d9(symTable,recordTable,pruneImdtRels,performIO,signalHandler,iter,ctr,inputDirectory,outputDirectory,*rel_delete_add_6fd868847292dbea,*rel_delete_leader_c04a5d036082e503,*rel_delete_var_73e06489152dbaa5,*rel_delta_add_241d705dc2fb23df,*rel_delta_eql_fdc75db4daac3372,*rel_delta_leader_d4159f531d436f83,*rel_delta_var_789565ec55b51a31,*rel_new_add_954a8c50e586f068,*rel_new_eql_10ebb01129546352,*rel_new_leader_99e6be51e44547e4,*rel_new_var_7aacd8d7c9129d14,*rel_reject_add_d8fb12f9ecd20122,*rel_reject_leader_c121991f9eab43a8,*rel_reject_var_3661e6768640ec8b,*rel_N_913bf6e156bb077c,*rel_add_48c57da858454f79,*rel_add_prep_e8dfec160429ed9e,*rel_eql_e1be027843ac9bc5,*rel_leader_d565398e1ef92697,*rel_var_09870be8e1a4a08e),
stratum_add_prep_ad75c73511997080(symTable,recordTable,pruneImdtRels,performIO,signalHandler,iter,ctr,inputDirectory,outputDirectory,*rel_delta_add_prep_81473cce7460e2b6,*rel_new_add_prep_d729e5114de538fd,*rel_N_913bf6e156bb077c,*rel_add_prep_e8dfec160429ed9e),
stratum_class_a21f43f864200ec6(symTable,recordTable,pruneImdtRels,performIO,signalHandler,iter,ctr,inputDirectory,outputDirectory,*rel_class_9017e5267072d9ea,*rel_eql_e1be027843ac9bc5),
stratum_root_97ddb9257bc55be8(symTable,recordTable,pruneImdtRels,performIO,signalHandler,iter,ctr,inputDirectory,outputDirectory,*rel_add_48c57da858454f79,*rel_leader_d565398e1ef92697,*rel_root_4971aadef59ffd68,*rel_var_09870be8e1a4a08e){
addRelation("N", wrapper_rel_N_913bf6e156bb077c, true, false);
addRelation("add_prep", wrapper_rel_add_prep_e8dfec160429ed9e, false, false);
addRelation("add", wrapper_rel_add_48c57da858454f79, false, false);
addRelation("eql", wrapper_rel_eql_e1be027843ac9bc5, false, false);
addRelation("leader", wrapper_rel_leader_d565398e1ef92697, false, true);
addRelation("var", wrapper_rel_var_09870be8e1a4a08e, false, false);
addRelation("class", wrapper_rel_class_9017e5267072d9ea, false, true);
addRelation("root", wrapper_rel_root_4971aadef59ffd68, false, true);
ProfileEventSingleton::instance().setOutputFile(profiling_fname);
}

 Sf_subsumption::~Sf_subsumption(){
}

void Sf_subsumption::runFunction(std::string inputDirectoryArg,std::string outputDirectoryArg,bool performIOArg,bool pruneImdtRelsArg){

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
ProfileEventSingleton::instance().startTimer();
ProfileEventSingleton::instance().makeTimeEvent("@time;starttime");
{
Logger logger("@runtime;", 0);
ProfileEventSingleton::instance().makeConfigRecord("relationCount", std::to_string(8));{
	Logger logger(R"_(@runtime;)_",iter);
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
stratum_add_14722fa4ca06c6d9.run(args, ret);
}
{
 std::vector<RamDomain> args, ret;
stratum_class_a21f43f864200ec6.run(args, ret);
}
{
 std::vector<RamDomain> args, ret;
stratum_root_97ddb9257bc55be8.run(args, ret);
}
}
}
ProfileEventSingleton::instance().stopTimer();
dumpFreqs();

// -- relation hint statistics --
signalHandler->reset();
}

void Sf_subsumption::run(){
runFunction("", "", false, false);
}

void Sf_subsumption::runAll(std::string inputDirectoryArg,std::string outputDirectoryArg,bool performIOArg,bool pruneImdtRelsArg){
runFunction(inputDirectoryArg, outputDirectoryArg, performIOArg, pruneImdtRelsArg);
}

void Sf_subsumption::printAll([[maybe_unused]] std::string outputDirectoryArg){
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","a\tb"},{"auxArity","0"},{"name","leader"},{"operation","output"},{"output-dir","subsumption"},{"params","{\"records\": {}, \"relation\": {\"arity\": 2, \"params\": [\"a\", \"b\"]}}"},{"types","{\"ADTs\": {\"+:Id\": {\"arity\": 2, \"branches\": [{\"name\": \"Add\", \"types\": [\"+:Id\", \"+:Id\"]}, {\"name\": \"Var\", \"types\": [\"i:number\"]}], \"enum\": false}}, \"records\": {}, \"relation\": {\"arity\": 2, \"types\": [\"+:Id\", \"+:Id\"]}}"}});
if (!outputDirectoryArg.empty()) {directiveMap["output-dir"] = outputDirectoryArg;}
IOSystem::getInstance().getWriter(directiveMap, symTable, recordTable)->writeAll(*rel_leader_d565398e1ef92697);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","a"},{"auxArity","0"},{"name","class"},{"operation","output"},{"output-dir","subsumption"},{"params","{\"records\": {}, \"relation\": {\"arity\": 1, \"params\": [\"a\"]}}"},{"types","{\"ADTs\": {\"+:Id\": {\"arity\": 2, \"branches\": [{\"name\": \"Add\", \"types\": [\"+:Id\", \"+:Id\"]}, {\"name\": \"Var\", \"types\": [\"i:number\"]}], \"enum\": false}}, \"records\": {}, \"relation\": {\"arity\": 1, \"types\": [\"+:Id\"]}}"}});
if (!outputDirectoryArg.empty()) {directiveMap["output-dir"] = outputDirectoryArg;}
IOSystem::getInstance().getWriter(directiveMap, symTable, recordTable)->writeAll(*rel_class_9017e5267072d9ea);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","i\ta"},{"auxArity","0"},{"name","root"},{"operation","output"},{"output-dir","subsumption"},{"params","{\"records\": {}, \"relation\": {\"arity\": 2, \"params\": [\"i\", \"a\"]}}"},{"types","{\"ADTs\": {\"+:Id\": {\"arity\": 2, \"branches\": [{\"name\": \"Add\", \"types\": [\"+:Id\", \"+:Id\"]}, {\"name\": \"Var\", \"types\": [\"i:number\"]}], \"enum\": false}}, \"records\": {}, \"relation\": {\"arity\": 2, \"types\": [\"i:number\", \"+:Id\"]}}"}});
if (!outputDirectoryArg.empty()) {directiveMap["output-dir"] = outputDirectoryArg;}
IOSystem::getInstance().getWriter(directiveMap, symTable, recordTable)->writeAll(*rel_root_4971aadef59ffd68);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
}

void Sf_subsumption::loadAll([[maybe_unused]] std::string inputDirectoryArg){
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","n"},{"auxArity","0"},{"fact-dir","."},{"filename","N.in"},{"name","N"},{"operation","input"},{"params","{\"records\": {}, \"relation\": {\"arity\": 1, \"params\": [\"n\"]}}"},{"types","{\"ADTs\": {\"+:Id\": {\"arity\": 2, \"branches\": [{\"name\": \"Add\", \"types\": [\"+:Id\", \"+:Id\"]}, {\"name\": \"Var\", \"types\": [\"i:number\"]}], \"enum\": false}}, \"records\": {}, \"relation\": {\"arity\": 1, \"types\": [\"i:number\"]}}"}});
if (!inputDirectoryArg.empty()) {directiveMap["fact-dir"] = inputDirectoryArg;}
IOSystem::getInstance().getReader(directiveMap, symTable, recordTable)->readAll(*rel_N_913bf6e156bb077c);
} catch (std::exception& e) {std::cerr << "Error loading N data: " << e.what() << '\n';}
}

void Sf_subsumption::dumpInputs(){
try {std::map<std::string, std::string> rwOperation;
rwOperation["IO"] = "stdout";
rwOperation["name"] = "N";
rwOperation["types"] = "{\"relation\": {\"arity\": 1, \"auxArity\": 0, \"types\": [\"i:number\"]}}";
IOSystem::getInstance().getWriter(rwOperation, symTable, recordTable)->writeAll(*rel_N_913bf6e156bb077c);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
}

void Sf_subsumption::dumpOutputs(){
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

SymbolTable& Sf_subsumption::getSymbolTable(){
return symTable;
}

RecordTable& Sf_subsumption::getRecordTable(){
return recordTable;
}

void Sf_subsumption::setNumThreads(std::size_t numThreadsValue){
SouffleProgram::setNumThreads(numThreadsValue);
symTable.setNumLanes(getNumThreads());
recordTable.setNumLanes(getNumThreads());
}

void Sf_subsumption::executeSubroutine(std::string name,const std::vector<RamDomain>& args,std::vector<RamDomain>& ret){
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
if (name == "root") {
stratum_root_97ddb9257bc55be8.run(args, ret);
return;}
fatal(("unknown subroutine " + name).c_str());
}

void Sf_subsumption::dumpFreqs(){
}

} // namespace souffle
namespace souffle {
SouffleProgram *newInstance_subsumption(){return new Sf_subsumption;}
SymbolTable *getST_subsumption(SouffleProgram *p){return &reinterpret_cast<Sf_subsumption*>(p)->getSymbolTable();}
} // namespace souffle

#ifndef __EMBEDDED_SOUFFLE__
#include "souffle/CompiledOptions.h"
int main(int argc, char** argv)
{
try{
souffle::CmdOptions opt(R"(subsumption.dl)",
R"()",
R"()",
true,
R"(subsumption.out.log)",
1);
if (!opt.parse(argc,argv)) return 1;
souffle::Sf_subsumption obj(opt.getProfileName());
#if defined(_OPENMP) 
obj.setNumThreads(opt.getNumJobs());

#endif
souffle::ProfileEventSingleton::instance().makeConfigRecord("", opt.getSourceFileName());
souffle::ProfileEventSingleton::instance().makeConfigRecord("fact-dir", opt.getInputFileDir());
souffle::ProfileEventSingleton::instance().makeConfigRecord("jobs", std::to_string(opt.getNumJobs()));
souffle::ProfileEventSingleton::instance().makeConfigRecord("output-dir", opt.getOutputFileDir());
souffle::ProfileEventSingleton::instance().makeConfigRecord("version", "2.3-82-gecee065f5");
obj.runAll(opt.getInputFileDir(), opt.getOutputFileDir());
return 0;
} catch(std::exception &e) { souffle::SignalHandler::instance()->error(e.what());}
}
#endif

namespace souffle {
class factory_Sf_subsumption: souffle::ProgramFactory {
public:
SouffleProgram* newInstance();
 factory_Sf_subsumption();
private:
};
} // namespace souffle
namespace souffle {
SouffleProgram* factory_Sf_subsumption::newInstance(){
return new Sf_subsumption();
}

 factory_Sf_subsumption::factory_Sf_subsumption():
ProgramFactory("subsumption"){
}

} // namespace souffle
namespace souffle {

#ifdef __EMBEDDED_SOUFFLE__
extern "C" {
factory_Sf_subsumption __factory_Sf_subsumption_instance;
}
#endif
} // namespace souffle

