<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:xs="http://www.w3.org/2001/XMLSchema" version="2.0" exclude-result-prefixes="xs">
    <xsl:output method="xml"/>
    <xsl:strip-space elements="*" />
    <xsl:template match="node()|@*">
        <xsl:copy>
            <xsl:apply-templates select="node()|@*"/>
        </xsl:copy>
    </xsl:template>
    <xsl:template match="errors">
        <xsl:copy>
            <xsl:apply-templates select="node()|@*"/>
            <xsl:for-each select="//method[count(object) &gt; 1]">
                <error type="duplicate" pos="0">
                    <xsl:attribute name="line">
                        <xsl:value-of select="mentioned/where[1]"/>
                    </xsl:attribute>
                    <xsl:text>method </xsl:text>
                    <xsl:value-of select="id"/>
                    <xsl:text> has multiple objects: &quot;</xsl:text>
                    <xsl:value-of select="object" separator="&quot;, &quot;"/>
                    <xsl:text>&quot;</xsl:text>
                </error>
            </xsl:for-each>
        </xsl:copy>
    </xsl:template>
    <xsl:template match="method[count(object) &gt; 1]">
        <xsl:copy>
            <xsl:apply-templates select="(node() except object)|@*"/>
            <object>
                <xsl:value-of select="object[1]"/>
            </object>
        </xsl:copy>
    </xsl:template>
</xsl:stylesheet>