#SSH is great

But you need to type your username and password.  This is

1.    annoying
2.    not secure

so we use public and private key pairs to handle our logins and information exchange.  This is

1.  awesome
2.  convenient
3.  sometimes still not secure

##Task 1 - SSH Setup

First check the version of OpenSSH you have installed

> ssh -V

It should be > 6.5 -- if not, upgrade.  Now.  The latest version of Ubuntu ships with 6.6.1p1, Arch is running 6.7p1.  OSX?  

###Generate new SSH Keys
Defaults for keypairs are a little bit weak -- you need two pairs of keys:
1.  ed25519 key -- the latest standard key, based on elliptic curve craziness and very secure.  This will become the default keytype in about a year.
2. rsa key -- because lots of people won't update their systems and all current systems support rsa

```
ssh-keygen -t ed25519 -o -a 100
ssh-keygen -t rsa -b 4096 -o -a 100
```
-t = keytype

-b = bits in the key (higher is better)

-o -a = hardens passphrase against brute forcing

Choose a good passphrase.  If your private key is stolen, it's the only thing protecting you from someone accessing all of your machines.

###Copy keys to blackbird

```
cd ~/.ssh
ssh-copy-id -i id_ed25519 blackbird.seas.gwu.edu
ssh-copy-id -i id_rsa blackbird.seas.gwu.edu
```
###Confirm you can log in with your key

```
ssh blackbird.seas.gwu.edu
exit
```

###Disable password logins

On your machine in /etc/ssh/sshd_config set

```
PasswordAuthentication no
ChallengeResponseAuthentication no
```

(I'll change it on blackbird)

Now, unless someone has a public key installed on your system, they can't log in.  They also can't brute-force attack a username+password combination because those don't exist anymore.

Yay!

###Make it more convenient

If your private key passphrase is long and complicated that's

1.   good
2.   a pain in the ass to type everytime

so we'll install `keychain` to make it easier.

> sudo pacman -S keychain

or

> sudo apt-get install keychain

####Load ssh-agent using keychain

> eval \`keychain --eval id_ed25519 id_rsa`

Now there's an ssh-agent running that stores your passphrase for your current session.  Try logging in to blackbird again.

Now append the keychain line to the end of your .bashrc (or .zshrc) and you'll only be prompted for your passphrases when you first log in.

ssh-copy-id to colonial one?

###Github

Go to: https://github.com/settings/ssh

Upload your id_ed25519.pub key

Now go to your local AeroPython git repo, cd into the config directory and edit the config file

```
cd AeroPython/.git
vim config
```

Under remote, change

> url = https://github.com/barbagroup/AeroPython.git

to

> url = git@github.com:barbagroup/AeroPython.git

Now you never have to type your github username+password again.  (If you clone the repo using the SSH address initially then you don't need to make this change)

##Awesome SSH utilities

###sshfs

Mount a directory on a remote machine via SSH on your local machine.  This is how we're going to be sharing files in the new lab.

> sudo pacman -S sshfs

> sudo apt-get install sshfs

Now create a local mountpoint and use sshfs to mount this folder from blackbird

```
mkdir mnt
sshfs blackbird.seas.gwu.edu:/home/gil/ ~/mnt
```

to unmount

> fusermount -u ~/mnt

##SSH shortcuts

Edit

`~/.ssh/config`


###SSH Configuration Files

*  /etc/ssh/ssh_config -- ssh client configuration
* /etc/ssh/sshd_config -- ssh server configuration
