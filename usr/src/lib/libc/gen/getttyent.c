/*
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "@(#)getttyent.c	5.8 (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <ttyent.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

static char zapchar;
static FILE *tf;

struct ttyent *
getttynam(tty)
	char *tty;
{
	register struct ttyent *t;

	setttyent();
	while (t = getttyent())
		if (!strcmp(tty, t->ty_name))
			break;
	return(t);
}

struct ttyent *
getttyent()
{
	static struct ttyent tty;
	register int c;
	register char *p;
#define	MAXLINELENGTH	100
	static char line[MAXLINELENGTH];
	char *skip(), *value();

	if (!tf && !setttyent())
		return(NULL);
	for (;;) {
		if (!fgets(p = line, sizeof(line), tf))
			return(NULL);
		/* skip lines that are too big */
		if (!index(p, '\n')) {
			while ((c = getc(tf)) != '\n' && c != EOF)
				;
			continue;
		}
		while (isspace(*p))
			++p;
		if (*p && *p != '#')
			break;
	}

	zapchar = 0;
	tty.ty_name = p;
	p = skip(p);
	if (!*(tty.ty_getty = p))
		tty.ty_getty = tty.ty_type = NULL;
	else {
		p = skip(p);
		if (!*(tty.ty_type = p))
			tty.ty_type = NULL;
		else
			p = skip(p);
	}
	tty.ty_status = 0;
	tty.ty_window = NULL;

#define	scmp(e)	!strncmp(p, e, sizeof(e) - 1) && isspace(p[sizeof(e) - 1])
#define	vcmp(e)	!strncmp(p, e, sizeof(e) - 1) && p[sizeof(e) - 1] == '='
	for (; *p; p = skip(p)) {
		if (scmp(_TTYS_OFF))
			tty.ty_status &= ~TTY_ON;
		else if (scmp(_TTYS_ON))
			tty.ty_status |= TTY_ON;
		else if (scmp(_TTYS_SECURE))
			tty.ty_status |= TTY_SECURE;
		else if (vcmp(_TTYS_WINDOW))
			tty.ty_window = value(p);
		else
			break;
	}

	if (zapchar == '#' || *p == '#')
		while ((c = *++p) == ' ' || c == '\t')
			;
	tty.ty_comment = p;
	if (*p == 0)
		tty.ty_comment = 0;
	if (p = index(p, '\n'))
		*p = '\0';
	return(&tty);
}

#define	QUOTED	1

/*
 * Skip over the current field, removing quotes, and return a pointer to
 * the next field.
 */
static char *
skip(p)
	register char *p;
{
	register char *t;
	register int c, q;

	for (q = 0, t = p; (c = *p) != '\0'; p++) {
		if (c == '"') {
			q ^= QUOTED;	/* obscure, but nice */
			continue;
		}
		if (q == QUOTED && *p == '\\' && *(p+1) == '"')
			p++;
		*t++ = *p;
		if (q == QUOTED)
			continue;
		if (c == '#') {
			zapchar = c;
			*p = 0;
			break;
		}
		if (c == '\t' || c == ' ' || c == '\n') {
			zapchar = c;
			*p++ = 0;
			while ((c = *p) == '\t' || c == ' ' || c == '\n')
				p++;
			break;
		}
	}
	*--t = '\0';
	return(p);
}

static char *
value(p)
	register char *p;
{
	return((p = index(p, '=')) ? ++p : NULL);
}

setttyent()
{
	if (tf) {
		(void)rewind(tf);
		return(1);
	} else if (tf = fopen(_PATH_TTYS, "r"))
		return(1);
	return(0);
}

endttyent()
{
	int rval;

	if (tf) {
		rval = !(fclose(tf) == EOF);
		tf = NULL;
		return(rval);
	}
	return(1);
}
