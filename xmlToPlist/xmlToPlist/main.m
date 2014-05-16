//
//  main.m
//  xmlToPlist
//
//  Created by Ysan on 14-3-12.
//  Copyright (c) 2014年 Ysan. All rights reserved.
//

#import <Foundation/Foundation.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>


static xmlDocPtr
getDocPtr(char* docname) {
	xmlDocPtr doc = NULL;
	xmlKeepBlanksDefault(0);
    
	doc = xmlParseFile(docname);
	if(NULL == doc) {
		fprintf(stderr, "document cannot be parsed!\n");
		exit(1);
	}
	return doc;
}

static xmlXPathObjectPtr
getXPathObjectPtr(xmlDocPtr doc, xmlChar* xpath_exp) {
	xmlXPathObjectPtr result;
	xmlXPathContextPtr context;
	
	context = xmlXPathNewContext(doc);
	result = xmlXPathEvalExpression((const xmlChar*)xpath_exp, context);
	xmlXPathFreeContext(context);
    
	if(NULL == result) {
		fprintf(stderr, "eval expression error!\n");
		return NULL;
	}
	if(xmlXPathNodeSetIsEmpty(result->nodesetval)) {
		fprintf(stderr, "empty node set!\n");
		xmlXPathFreeObject(result);
		return NULL;
	}
	return result;
}

int main(int argc, const char * argv[])
{
    @autoreleasepool
    {
        char tmp[128];
        NSMutableArray *prov = [[NSMutableArray alloc] initWithCapacity: 100];
        NSMutableArray *arry = [[NSMutableArray alloc] initWithCapacity: 100];
        // insert code here...
        
        char* docname = "pcc.xml";
        xmlDocPtr doc = NULL;
        xmlXPathObjectPtr xpath_obj = NULL;
        xmlXPathObjectPtr xpath_obj1 = NULL;
        xmlNodeSetPtr nodeset = NULL;
        xmlNodeSetPtr nodeset2 = NULL;
        xmlChar* xpath_exp = (xmlChar*)"/China/province";
        xmlChar* uri;
        doc = getDocPtr(docname);
        xpath_obj = getXPathObjectPtr(doc, xpath_exp);
        
        if(NULL != xpath_obj)
        {
            nodeset = xpath_obj->nodesetval;
            int i = 0;
            for(i = 0; i < nodeset->nodeNr; i ++) {
                uri = xmlGetProp(nodeset->nodeTab[i],(const xmlChar*)"name");
                [prov addObject:[[NSString alloc] initWithUTF8String:(const char*)uri]];
                xmlFree(uri);
            }
            xmlXPathFreeObject(xpath_obj);
            xmlFreeDoc(doc);
            xmlCleanupParser();
        }
        NSMutableDictionary *dictFinal = [[NSMutableDictionary alloc] initWithCapacity:100];
        NSMutableDictionary *dict = [[NSMutableDictionary alloc] initWithCapacity:100];
        for (NSInteger i=0; i<[prov count]; i++)
        {
            NSMutableArray *city = [[NSMutableArray alloc] initWithCapacity: 100];
            snprintf(tmp, 128, "/China/province[@name='%s']/city",[[prov objectAtIndex:i] cStringUsingEncoding:NSUTF8StringEncoding]);//[NSString defaultCStringEncoding]]);
            doc = getDocPtr(docname);
            xpath_obj = getXPathObjectPtr(doc,(unsigned char*)tmp);
            if(NULL != xpath_obj)
            {
                nodeset = xpath_obj->nodesetval;
                int s = 0;
                for(s = 0; s < nodeset->nodeNr; s ++)
                {
                    uri = xmlGetProp(nodeset->nodeTab[s],(const xmlChar*)"name");
                    [city addObject:[[NSString alloc] initWithUTF8String:(const char*)uri]];
                    xmlFree(uri);
                }
                xmlXPathFreeObject(xpath_obj);
                xmlFreeDoc(doc);
                xmlCleanupParser();
                
                NSMutableArray *county = [[NSMutableArray alloc] initWithCapacity: 100];
                for (NSInteger j=0; j<[city count]; j++)
                {
                    snprintf(tmp, 128, "/China/province[@name='%s']/city[@name='%s']/county",[[prov objectAtIndex:i] cStringUsingEncoding:NSUTF8StringEncoding],[[city objectAtIndex:j] cStringUsingEncoding:NSUTF8StringEncoding]);
                    doc = getDocPtr(docname);
                    xpath_obj1 = getXPathObjectPtr(doc, (xmlChar*)tmp);
                    if(NULL != xpath_obj1)
                    {
                        nodeset2 = xpath_obj1->nodesetval;
                        int t = 0;
                        for(t = 0; t < nodeset2->nodeNr; t++)
                        {
                            uri = xmlGetProp(nodeset2->nodeTab[t],(const xmlChar*)"name");
                            [county addObject:[[NSString alloc] initWithUTF8String:(const char*)uri]];
                            xmlFree(uri);
                        }
                        xmlXPathFreeObject(xpath_obj1);
                        
                    }
                    //A->D
                    NSArray *a = [[NSArray alloc]initWithArray:county];
                    [county removeAllObjects];
                    [dict setObject:a forKey:[city objectAtIndex:j]];
                    //D->A
                    NSDictionary *d = [[NSDictionary alloc]initWithDictionary:dict];
                    [dict removeAllObjects];
                    [arry addObject:d];
                }
                //A->D
                [dictFinal setObject:[arry objectAtIndex:i] forKey:[prov objectAtIndex:i]];
            }
        }
        [dictFinal writeToFile:@"hello.plist" atomically:YES];
        xmlFreeDoc(doc);
        xmlCleanupParser();
        return 0;
    }
}