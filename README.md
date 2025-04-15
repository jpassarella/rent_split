# rent_split
I don't know if a README would provide much value here, but right now this is just a loop that prints out the ways to split an even integer.

If the rent is 5.00 (5 dollars or whatever currency you choose), then total rent is that number as an int without the decimal point, or 500.
So 27.82 -> 2782
4879.04 -> 487904
3.01 -> 301 (But this doesnt work with odd final digits right now, though that should be a quick change.)

Ultimately though, I realized this could be a simple program that asks users questions like the following:\n
If the rent split was X dollars for room A and Y dollars for room B, then which room would you want.
A few binary searches (or something similar) later and you hone in on the exact equilibrium value.

If the roommate does the same thing, a simple average would give a somewhat fair split of rent.

There is probably some economic principle that says I have it a little wrong, but I feel like the general idea is still good.

Suppose:
At $12 for the big room and $6 for the small room, Joe is ambivalent between the two.
And, at $10 for the big room and $8 for the small room, Tom is ambivalent between the two.
Then Joe should get the big room (because he values it more) and his rent should be $11.
And so Tom should get the small room (I guess economically speaking because he values the money saved more) and his rent should be $7.

A more complicated problem would be having 3 or more roommates.

Regardless though, this seems really simple and honestly quite useful. It probably exists already but I won't check because that might decrease my motivation to program it.
