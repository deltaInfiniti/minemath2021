#pragma once
/*
strlist_sup_dedupe
stringlist supliment for half-radix deduping
attempts to sort strings(byte*?) by dumping 2x radix buckets of 256 
first pass, take A=str.length-1(or 0), put node into basenodeslist[A]
with another table of nodes worknodeslist
for each basenodeslist, parse into worknodeslist in the same fasion as first pass, but with length-2(or 1)
once whole basenodeslist[] has been parsed into worknodeslist
inplace sort each worknodeslist[] by insertion sort
purge worknodeslist to deduped list, parse next pasenodeslist[] 

uses the SLIP struct and related functions
StringListItemPointer- slip
*/
#include<strlist.h>
#include<string>
#include<Windows.h>

using namespace std;
void slip_remove(slip vv) {
	slip l = vv->last;
	slip n = vv->next;
	if (l != NULL) l->next = n;
	if (n != NULL) n->last = l;
}
void slip_inject(slip vv, slip targ) {

	slip nex = targ->next;
	vv->last = targ;
	vv->next = nex;
	if (nex != NULL)nex->last = vv;
	targ->next = vv;
}
class strlist_dedupe {
	slip basenodes[256];
	slip worknodes[256];
	slip basenodesend[256];
	slip worknodesend[256];
public:
	slip deduped;
	int dedupedlen;

	strlist_dedupe() {
		//ZeroMemory(basenodes, sizeof(slip) * 256);
		//ZeroMemory(worknodes, sizeof(slip) * 256);
		for (int i = 0; i < 256; i++) {
			newSLIP("*base*",basenodes[i]);
			newSLIP("*end*", basenodes[i]->next);
			basenodesend[i] = basenodes[i]->next;
			basenodesend[i]->last = basenodes[i];
			newSLIP("*base*", worknodes[i]);
			newSLIP("*end*", worknodes[i]->next);
			worknodesend[i] = worknodes[i]->next;
			worknodesend[i]->last = worknodes[i];

		}
		newSLIP("*base*", deduped);
		newSLIP("*end*", deduped->next);
		deduped->next->last = deduped;

		dedupedlen = 0;
	}
	void dedupe_queue(string what);

	void check_worknodes() {
		int count = 0;
		slip targ;
		for (int i = 0; i < 256; i++) {
			targ = worknodes[i]->next;
			while (targ->name != "*end*") {
				count++;
				targ = targ->next;
				//cout << "tcount " << i << " : " << count << "           \r";
				if (count > 100000) {
					cout << "worknode " << i << " failed to find end               " << endl;
					pause();
					break;
				}
			}
			//cout << "tcount " << i << " : " << count << "           \n\n";
			count = 0;
		}

	}
	void dedupeout() {
		slip targ = deduped->next;
		int t = 0;
		while (targ->name != "*end*") {
			if (targ->name != "") {
				cout << targ->name << endl;
				t++;
			}
			targ = targ->next;
		}
		cout << "total in dedupe array: " << t << endl;
	}
	void onepass_worknodes() {
		slip outlist, * slide, * dtarg;
		//dedupdedlen = 0;

		for (int i = 0; i < 256; i++) {
			outlist = worknodes[i]->next;
			while (outlist->name != "*end*") {
				//if (outlist->name == "*end*")continue;
				slide = outlist->next;
				slip_remove(outlist);
				while (slide->name != "*end*") {
					if (slide->name == outlist->name) {
						dtarg = slide;
						slide = slide->next;
						slip_remove(dtarg);
						slip_delete(dtarg);
						//dtarg->name = "";
					}
					else slide = slide->next;
				}
				if (outlist->name != "") {
					slip_inject(outlist, deduped);
					dedupedlen++;
				}
				outlist = worknodes[i]->next;
			}
		}
	}
	void onepass_dedupe() {
		slip outlist, *slide, *dtarg;
		//dedupdedlen = 0;

		for (int i = 0; i < 256; i++) {
			outlist = basenodes[i]->next;
			while (outlist->name != "*end*") {
				//if (outlist->name == "*end*")continue;
				slide = outlist->next;
				slip_remove(outlist);
				while (slide->name != "*end*") {
					if (slide->name == outlist->name) {
						dtarg = slide;
						slide = slide->next;
						slip_remove(dtarg);
						slip_delete(dtarg);
						//dtarg->name = "";
					}
					else slide = slide->next;
				}
				if (outlist->name != "") {
					slip_inject(outlist, deduped);
					dedupedlen++;
				}
				outlist = basenodes[i]->next;
			}
		}
	}
	void onepass_dedupe_knowngood() {
		// simple, elegant, 1pass 256 bucket radix dedupe method.
		slip outlist, * slide, * dtarg;
		//dedupdedlen = 0;

		for (int i = 0; i < 256; i++) {
			outlist = basenodes[i]->next; // get first entry in basenode
			while (outlist->name != "*end*") { // loop through all entries
				//if (outlist->name == "*end*")continue;
				slide = outlist->next; // set slide to next item
				slip_remove(outlist); // remove this target from the basenodes list
				while (slide->name != "*end*") { // loop through the rest of the list
					if (slide->name == outlist->name) {// if a dupe is found
						dtarg = slide;
						slide = slide->next;
						slip_remove(dtarg);  // remove the dupe and incriment slide
						slip_delete(dtarg);
						//dtarg->name = "";
					}
					else slide = slide->next; // if not a dupe, incriment slide
				}
				if (outlist->name != "") { // if the node isn't blank
					slip_inject(outlist, deduped); // add it to deduped list
					dedupedlen++;
				}
				outlist = basenodes[i]->next; // get the 'next' node. since outlist was removed previously, next is first in list
			}
		}
	}
	void twopass_dedupe() {
		slip place, * next, * slide;
		int count, x, comphold, outcount = 0;
		int mcount = 0;
		for (int i = 0; i < 256; i++) {
			//cout << "outer loop start i:" << i << endl;
			mcount = 0;
			while (basenodes[i]->next != basenodesend[i]) {
				slip t = basenodes[i]->next;
				slip_remove(t);
				slip_inject(t, worknodes[(BYTE)t->name[t->name.length() - 2]]);
				outcount++;
				mcount++;
			}
			if (mcount == 0)continue;
			//cout << "after worknodes transfer outcount:" << outcount << endl;
			onepass_worknodes();
		}
	}
	void parse_dedupe() {
		slip place, * next, * slide;
		int count, x, comphold, outcount=0;
		int mcount = 0;
		for (int i = 0; i < 256; i++) {
			cout << "outer loop start i:" << i << endl;
			mcount = 0;
			while (basenodes[i]->next != basenodesend[i]) {
				slip t = basenodes[i]->next;
				slip_remove(t);
				slip_inject(t, worknodes[(BYTE)t->name[t->name.length() - 2]]);
				outcount++;
				mcount++;
			}
			if (mcount == 0)continue;
			cout << "after worknodes transfer outcount:" << outcount << endl;
			check_worknodes();
			for (int n = 0; n < 256; n++) {
				place = worknodes[n]->next;
				next = place->next;
				count = 1;
				while (place->name != "*end*") {
					x = 1;
					slide = worknodes[n]->next;
					comphold = -1;
					while (x < count || place->name=="*end*") {
						if (slide->name == ""||place==slide) {
							slide = slide->next;
							x++;
							continue;
						}
						comphold = abcomp(place->name, slide->name);
						if (comphold != -1)break;
						if (comphold == 0)break;
						if (comphold == 1)break;
						slide = slide->next;
						x++;
					}
					if (comphold == 0) {
						//cout << "found dupe{base,slide}:" << place->name << "  " << slide->name << endl;
						place->name = "";
						place = next;
						next = next->next;
						continue;
					}
					if (place == slide) {
						count++;
						place = next;
						next = next->next;
						continue;
					}
					if (x == count || comphold == -1) {
						slip_remove(place);
						slip_inject(place, slide->last);
						count++;
					}
					place = next;
					next = next->next;

				}
				place = worknodes[n]->next;
				slip nxt = place->next;
				for (int p = 1; true; p++) {//p < count
					if (place->name == "*end*")break;
					if (place->name == "") {
						place = nxt;
						nxt = nxt->next;
						continue;
					}
					slip_remove(place);
					slip_inject(place, deduped);
					dedupedlen++;
					place = nxt;
					nxt = nxt->next;
				//	cout << "looped dupeout" << endl;
				}
				check_worknodes();
			}
		}
	

													
						

			// sort nodes in worknodes in place deduping
			// purge worknodes to deduped 

	}

};

void strlist_dedupe::dedupe_queue(string what) {
	
	slip_insert(basenodes[(BYTE)what[what.length() - 1]], what);
}
