type t('value, 'id) = Belt.Set.t('value, 'id);

/**
 * Construct a new, empty set.
 */
let empty: (
            (module Belt.Id.Comparable with type t = 'value and type identity = 'id)
          ) => Belt.Set.t('value, 'id) =
  Belt.Set.make(~id=_);

/**
 * `fromArray((module Comparable), array(value))`
 * converts an array of values into a new set of those values,
 * ordered by the comparator function `Comparable.cmp`.
 */
let fromArray: (
            (module Belt.Id.Comparable with type t = 'value and type identity = 'id),
            array('value)
          ) => Belt.Set.t('value, 'id) =
  (id, value) => Belt.Set.fromArray(~id, value);

/**
 * `fromList((module Comparable), list(value))`
 * converts a list of values into a new set of those values,
 * ordered by the comparator function `Comparable.cmp`.
 */
let fromList: (
            (module Belt.Id.Comparable with type t = 'value and type identity = 'id),
            list('value)
          ) => Belt.Set.t('value, 'id) =
  (id, value) => Belt.Set.fromArray(~id, Belt.List.toArray(value));

/**
 * Determine whether a set is empty.
 */
let isEmpty: t('value, 'id) => bool =
  Belt.Set.isEmpty;

/**
 * Determine whether a set contains a given value.
 */
let contains: ('value, t('value, 'id)) => bool =
  (value, set) => Belt.Set.has(set, value);

/**
 * Immutably add a value to a set. If the value already exists
 * in the set, the original set (physical reference) is returned
 * unchanged. Otherwise, a new copy of the set is returned
 * containing the value.
 */
let add: ('value, t('value, 'id)) => t('value, 'id) =
  (value, set) => Belt.Set.add(set, value);

/**
 * Immutably merge an array of values into a set. Note: unlike `add`
 * If the set already contains all the values in the array, the
 * return value **may or may not be a new reference**. Otherwise,
 * a new set reference is returned.
 */
let mergeMany: (array('value), t('value, 'id)) => t('value, 'id) =
  (value, set) => Belt.Set.mergeMany(set, value);

/**
 * Immutably remove a value from a set. If the value is not found
 * in the set, the original set (physical reference) is returned
 * unchanged. Otherwise, a new set is returned containing the value.
 */
let remove: ('value, t('value, 'id)) => t('value, 'id) =
  (value, set) => Belt.Set.remove(set, value);

/**
 * Immutably remove multiple values from a set. Note: unlike `remove`
 * If none of the values in the array are found in the set, the
 * return value **may or may not be a new reference**. Otherwise, a
 * new set reference is returned.
 */
let removeMany: (array('value), t('value, 'id)) => t('value, 'id) =
  (value, set) => Belt.Set.removeMany(set, value);

/**
 * Immutably update a set with a new value. If an equivalent value
 * already exists in the set, it will be immutably removed before
 * adding the new value. In ether case, a new physical reference
 * to the set will be returned. **Note: unlike `add`, `update`
 * guarantees that the value's physical reference will be added to
 * the set.**
 */
let update: ('value, t('value, 'id)) => t('value, 'id) =
  (value, set) => Belt.Set.add(Belt.Set.remove(set, value), value);

/**
 * Returns a new set representing the union of two sets. E.g.:
 * ```ocaml
 *  let s1 = fromList([1, 3, 4, 5, 2, 1]);
 *  let s2 = fromList([1, 0, 3, 2, 9]);
 *  let result = union(s1, s2) |> toList;
 *  // result: [0, 1, 2, 3, 4, 5, 9]
 * ```
 */
let union: (t('value, 'id), t('value, 'id)) => t('value, 'id) =
  Belt.Set.union;

/**
 * Returns a new set representing the intersection of two sets.
 * E.g.:
 * ```ocaml
 * let s1 = fromList([0, 1, 2, 3, 4, 1]);
 * let s2 = fromList([0, 3, 9, 8, 10]);
 * let result = intersect(s1, s2) |> toList;
 * // result: [0, 3]
 * ```
 */
let intersect: (t('value, 'id), t('value, 'id)) => t('value, 'id) =
  Belt.Set.intersect;

/**
 * Returns a new set which contains all the elements of the first
 * set that are not present in the second set. **Note: The argument order
 * is significant for this function**.
 * E.g.:
 * ```ocaml
 * let s1 = fromList([0, 1, 2, 3, 4, 1]);
 * let s2 = fromList([0, 3, 9, 8, 10]);
 * 
 * let result1 = diff(s1, s2) |> toList;
 * // result: [1, 2, 4];
 * 
 * let result2 = diff(s2, s1) |> toList;
 * // result: [8, 9, 10];
 * ```
 */
let diff: (t('value, 'id), t('value, 'id)) => t('value, 'id) = Belt.Set.diff;

/**
 * `subset(s1, s2)` will return `true` if `s2` is a subset of `s1`.
 * **Note: The argument order is significant for this function**.
 */
let subset: (t('value, 'id), t('value, 'id)) => bool = Belt.Set.subset;

/**
 * Returns an integer value of `-1 | 0 | 1`, representing the total
 * ordering between two sets. This can be used as a comparator function
 * to determine the ordering of nested sets (e.g. `Set.t(Set.t('a))`);
 * **Note: The argument order is significant for this function**.
 * 
 * TODO: document the behavior based on argument order.
 */
let compare: (t('value, 'id), t('value, 'id)) => int = Belt.Set.cmp;

/**
 * Determine whether two sets are equivalent.
 */
let eq: (t('value, 'id), t('value, 'id)) => bool = Belt.Set.eq;

/**
 * Apply a function to each element of a set, in increasing
 * order.
 */
let forEach: ('value => unit, t('value, 'id)) => unit =
  (fn, set) => Belt.Set.forEach(set, fn);

/**
 * Iterate over the values of a set in increasing order,
 * accumulating a final value of an arbitraty type.
 */
let foldLeft: (('acc, 'value) => 'acc, 'acc, t('value, 'id)) => 'acc =
  (fn, acc, set) => Belt.Set.reduce(set, acc, fn);

/**
 * Determine whether a given predicate holds true for all values
 * in a given set.
 */
let all: ('value => bool, t('value, 'id)) => bool =
  (predicate, set) => Belt.Set.every(set, predicate);

/**
 * Determine whether a given predicate holds true for at least
 * one value in a given set.
 */
let any: ('value => bool, t('value, 'id)) => bool =
  (predicate, set) => Belt.Set.some(set, predicate);

/**
 * Create a new set from another set containing only the values
 * which pass a given test (the predicate funciton).
 */
let filter: ('value => bool, t('value, 'id)) => t('value, 'id) =
  (predicate, set) => Belt.Set.keep(set, predicate);

/**
 * Immutably divide a set into a tuple of two sets, where the first
 * set contains all the values which pass the predicate function test,
 * and the second one contains all the values which fail.
 * **Note: The argument order is significant for this function**.
 * 
 * TODO: document the behavior based on argument order.
 */
let partition: ('value => bool, t('value, 'id)) => (t('value, 'id), t('value, 'id)) =
  (predicate, set) => Belt.Set.partition(set, predicate);

/**
 * Returns the total number of elements in a set.
 */
let length: t('value, 'id) => int =
  Belt.Set.size;

/**
 * Creates a new array containing all elements of the set in
 * ascending order based on the associated comparator function.
 */
let toArray: t('value, 'id) => array('value) =
  Belt.Set.toArray;

/**
 * Creates a new list containing all elements of the set in
 * ascending order based on the associated comparator function.
 */
let toList: t('value, 'id) => list('value) =
  Belt.Set.toList;

/**
 * Optionally returns the lowest ordered element in a given set.
 * Returns `None` if the set is empty.
 */
let minimum: t('value, 'id) => option('value) =
  Belt.Set.minimum;

/**
 * Optionally returns the highest ordered element in a given set.
 * Returns `None` if the set is empty.
 */
let maximum: t('value, 'id) => option('value) =
  Belt.Set.maximum;

/**
 * Optionally returns an equivalent element from a set.
 * Returns `None` if no equivalent element is found, or the
 * set is empty.
 */
let get: ('value, t('value, 'id)) => option('value) =
  (value, set) => Belt.Set.get(set, value);

/**
 * Returns an equivalent element from a set if one exists,
 * or else returns a specified default value.
 */
let getOrElse: ('value, 'value ,t('value, 'id)) => 'value =
  (value, default, set) => Relude_Option_Base.getOrElse(default, Belt.Set.get(set, value));

/**
 * TODO: Test & document this function.
 */
let split: ('value, t('value, 'id)) => ((t('value, 'id), t('value, 'id)), bool) =
  (value, set) => Belt.Set.split(set, value);


module type SET = {
  type value;
  module Comparable: {
    type identity;
    type t;
  };
  type t = Belt.Set.t(value, Comparable.identity);
  let empty: t;
  let fromArray: array(value) => t;
  let fromList: list(value) => t;
  let isEmpty: t => bool;
  let contains: (value, t) => bool;
  let add: (value, t) => t;
  let mergeMany: (array(value), t) => t;
  let remove: (value, t) => t;
  let removeMany: (array(value), t) => t;
  let update: (value, t) => t;
  let union: (t, t) => t;
  let intersect: (t, t) => t;
  let diff: (t, t) => t;
  let subset: (t, t) => bool;
  let compare: (t, t) => int;
  let eq: (t, t) => bool;
  let forEach: (value => unit, t) => unit;
  let foldLeft: (('a, value) => 'a, 'a, t) => 'a;
  let all: (value => bool, t) => bool;
  let any: (value => bool, t) => bool;
  let filter: (value => bool, t) => t;
  let partition: (value => bool, t) => (t, t);
  let length: t => int;
  let toArray: t => array(value);
  let toList: t => list(value);
  let minimum: t => option(value);
  let maximum: t => option(value);
  let get: (value, t) => option(value);
  let getOrElse: (value, value, t) => value;
  let split: (value, t) => ((t, t), bool);
};

module WithOrd = (M: BsAbstract.Interface.ORD)
// : (SET with type value = M.t)
=> {
  module Comparable =
    Belt.Id.MakeComparable({
      type t = M.t;
      let cmp = (a, b) => M.compare(a, b) |> Relude_Ordering.toInt;
    });
  type value = M.t;
  type nonrec t = t(value, Comparable.identity);
  let empty: t = empty((module Comparable));
  let fromArray: array(value) => t = fromArray(module Comparable);
  let fromList: list(value) => t = fromList(module Comparable);
  let isEmpty: t => bool = isEmpty;
  let contains: (value, t) => bool = contains;
  let add: (value, t) => t = add;
  let mergeMany: (array(value), t) => t = mergeMany;
  let remove: (value, t) => t = remove;
  let removeMany: (array(value), t) => t = removeMany;
  let update: (value, t) => t = update;
  let union: (t, t) => t = union;
  let intersect: (t, t) => t = intersect;
  let diff: (t, t) => t = diff;
  let subset: (t, t) => bool = subset;
  let compare: (t, t) => int = compare;
  let eq: (t, t) => bool = eq;
  let forEach: (value => unit, t) => unit = forEach;
  let foldLeft: (('acc, value) => 'acc, 'acc, t) => 'acc = foldLeft;
  let all: (value => bool, t) => bool = all;
  let any: (value => bool, t) => bool = any;
  let filter: (value => bool, t) => t = filter;
  let partition: (value => bool, t) => (t, t) = partition;
  let length: t => int = length;
  let toArray: t => array(value) = toArray;
  let toList: t => list(value) = toList;
  let minimum: t => option(value) = minimum;
  let maximum: t => option(value) = maximum;
  let get: (value, t) => option(value) = get;
  let getOrElse: (value, value, t) => value = getOrElse;
  let split: (value, t) => ((t, t), bool) = split;
};
