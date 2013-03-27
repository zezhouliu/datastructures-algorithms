(* Red Black Tree *)

(* SIGNATURES *)

(* Signature for Red Black Tree *)
module type RBTREE = 
sig 
	exception Invalid_argument

	type color

	type elt 

	type rbtree

	val empty

	val mem

	val balance

	val insert
end

(* A signature for a module which defines a type and
 * how to compare values of that type, as well as ways of generating
 * values of that type. *)
module type COMPARABLE_AND_GENABLE =
sig
  type t
  val compare : t -> t -> order
  val to_string : t -> string

  (* See the testing.ml for an explanation of
   * what these "generate*" functions do, and why we included them in
   * this signature. *)
  (* Generate a value of type t *)
  val generate: unit -> t
  (* Generate a value of type t that is greater than the argument. *)
  val generate_gt: t -> unit -> t
  (* Generate a value of type t that is less than the argument. *)
  val generate_lt: t -> unit -> t
  (* Generate a value of type t that is between argument 1 and argument 2.
   * Returns None if there is no value between argument 1 and argument 2. *)
  val generate_between: t -> t -> unit -> t option
end

(* An example implementation of the COMPARABLE_AND_GENABLE signature *)
module IntCompare : COMPARABLE_AND_GENABLE with type t=int =
struct
  type t = int
  let compare x y = if x < y then Less else if x > y then Greater else Equal
  let to_string = string_of_int


  let generate () = 0
  let generate_gt x () = x + 1
  let generate_lt x () = x - 1
  let generate_between x y () =
    let (lower, higher) = (min x y, max x y) in
    if higher - lower < 2 then None else Some (higher - 1)
end

(* FUNCTORS *)
module RBTree(C : COMPARABLE_AND_GENABLE) : RBTREE with type elt = C.t =
struct
	exception Invalid_argument

	type color = Red | Black

	type elt = C.t

	type rbtree = 
		| Leaf
		| Node of color * elt * rbtree * rbtree

	let empty = Leaf 

	let rec mem x = 
		match x with
		|Leaf -> false
		| Node (_, y, left, right) -> 
			x = y || (x < y && mem x left) || (x > y && mem x right)

	(* helper function that balances tree *)
	let balance mytree =
		match mytree with
		| Black, z, Node (Red, y, Node (Red, x, a, b), c), d
		| Black, z, Node (Red, x, a, Node (Red, y, b, c)), d
		| Black, x, a, Node (Red, z, Node (Red, y, b, c), d)
		| Black, x, a, Node (Red, y, b, Node (Red, z, c, d)) ->
			Node (Red, y, Node (Black, x, a, b), Node (Black, z, c, d))
		| a, b, c, d -> Node (a, b, c, d)

	(* insert function into red black tree *)
	let insert x stree =
		let rec ins x = 
			match x with
			|Leaf -> Node (Red, x, Leaf, Leaf)
			| Node (color, y, a, b) as s ->
				if x < y then balance (color, y, ins a, b)
				else if x > y then balance (color, y, a, ins b)
				else s
		in
		match ins s with (* guaranteed to be nonempty *)
		| Node (_, y, a, b) -> Node (Black, y, a, b)
		| Leaf -> raise (Invalid_argument "insert")

end

module IntTree = RBTree(IntCompare)
