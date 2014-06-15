<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns:xs="http://www.w3.org/2001/XMLSchema"
    xmlns:r="org.requs.facet.uml.Plant" version="2.0"
    exclude-result-prefixes="xs r">
    <xsl:output method="xml"/>
    <xsl:strip-space elements="*" />
    <xsl:template match="method">
        <xsl:copy>
            <xsl:apply-templates select="node()|@*"/>
            <xsl:variable name="uml">
                @startuml
                Bob -> Alice : hello
                @enduml
            </xsl:variable>
            <svg><xsl:value-of select="r:svg($uml)"/></svg>
        </xsl:copy>
    </xsl:template>
    <xsl:template match="node()|@*">
        <xsl:copy>
            <xsl:apply-templates select="node()|@*"/>
        </xsl:copy>
    </xsl:template>
</xsl:stylesheet>
