---
layout: default
title: "Facebook SRS, Example"
date: 2014-06-01
description:
  Requs is a controlled natural language (CNL) for
  software requirements specification
---

This is an example SRS of Facebook, in
[Requs syntax](./syntax.html):

{% highlight requs %}
User is "a human being".
User has: email, password, name.

UC1 where User (a user) socializes:
  1. The user identifies himself;
  2. The user invites User (a user);
  3. The user accepts Invitation (an invite);
  4. The user publishes StatusUpdate (an update);
  5. The user scrolls Timeline (a timeline).

StatusUpdate is "a text/image/video information posted by a user".
StatusUpdate contains: text, date, author as User.

Timeline is a "list of status updates from user friends".
Timeline contains: update-s as StatusUpdate.

Invitation is a "request to become a friend sent from one user to another".
Invitation has: author as User and friend as User.

UC2 where User identifies himself:
  "The user enters his email and password, if he has them. Otherwise,
  he registers in the system first, providing his email, full
  name, password, and phone number".

UC3 where User (a user) invites User (a friend):
  1. The user reads the friend
    "finding him in a list of all registered users";
  2. The user creates the invitation.
UC3/2 when "the user is banned by the friend":
  1. Fail since "the user is not allowed to invite this friend".

UC4 where User (a user) accepts Invitation (an invitation):
  1. The user reads the invitation;
  2. "User bans a requester, making impossible any more invitations from him";
  3. The user updates the invitation
    "adding the friend to his list of friends".

UC5 where User (a user) publishes StatusUpdate (an update):
  1. The user creates the update
    "and it automatically gets added to his Timeline".

UC6 where User (a user) scrolls Timeline:
  "The user lists all status updates created by his
  friends in a reversive chronological order".

UC1/UI must "be responsive, adapting itself to the width of device".

UC1/PERF must "guarantee a delivery of any HTTP response
  in less than 1 second, with standard equipment and normal
  load of the system".

UC1/SCALE must "handle any number (up to a billion) of users without
  performance degrading".
{% endhighlight %}
