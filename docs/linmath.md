# Ivy Linear Math Header (ivy_linmath.h)

This is a single header file with the implementation of linear algebra for
graphics and games programming. This was originally designed with the idea of
C11 in mind, but there is support planned for C99. It's part of the Ivy
Standard Library (ivystd), but it's planned to have support for using it
standalone.

You might ask "why do we need yet another maths library when there are
multiple good ones out there." Well, I don't like most of them, atleast the
ones made for C. They're either too performance focused, sacrificing DX, or
they are too minimalist. My goal for making this is that it's a capable to
make a whole game with, but also nice to use.

There is an exception of Handmade Math, which is really amazing! But I
decided to implement my own because it'll be good for learning and it saves
me from bringing an external dependency into ivystd.

# Credits
Credit towards Handmade Math, because this library is heavily inspired by it,
and for some of the code for matrices, I copied from HMM and did some
adjustments.

# How to use
Look at the comment in the top of the header