<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns:xs="http://www.w3.org/2001/XMLSchema"
    xmlns:r="org.requs.facet.XsltFuncs"
    version="2.0" exclude-result-prefixes="xs r">
    <xsl:output method="xml"/>
    <xsl:strip-space elements="*" />
    <xsl:template match="/spec">
        <xsl:copy>
            <xsl:apply-templates select="node()|@*"/>
        </xsl:copy>
    </xsl:template>
    <xsl:template match="method">
        <xsl:variable name="m">
            <xsl:copy>
                <xsl:apply-templates select="(node() except (id|mentioned|attributes|markdown))|@*"/>
            </xsl:copy>
        </xsl:variable>
        <xsl:copy>
            <xsl:attribute name="seal">
                <xsl:value-of select="r:seal($m)"/>
            </xsl:attribute>
            <xsl:apply-templates select="node()|@*"/>
        </xsl:copy>
    </xsl:template>
    <xsl:template match="node()|@*">
        <xsl:copy>
            <xsl:apply-templates select="node()|@*"/>
        </xsl:copy>
    </xsl:template>
</xsl:stylesheet>
